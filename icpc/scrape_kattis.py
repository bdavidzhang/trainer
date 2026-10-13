"""Scrape ICPC regional-level problem sources from open.kattis.com."""
import html
import json
import re
import sys
import urllib.parse

from .db import connect
from .http import fetch

BASE = "https://open.kattis.com"
MIN_YEAR = 2016
INCLUDE = re.compile(
    r"ICPC|Regional|NWERC|NCPC|Nordic Collegiate|BAPC|GCPC|German Collegiate|CERC|SWERC|SEERC|UKIEPC|"
    r"Italian Collegiate|North America|Mid-Central|Rocky Mountain|PacNW|Pacific Northwest|Southeast USA|"
    r"Southern California|Greater New York|Mid-Atlantic|East.Central|South Central|World Finals", re.I)
EXCLUDE = re.compile(r"Practice|High School|ICPC Challenge|SG Preliminary", re.I)


def kind_of(name):
    if "World Finals" in name:
        return "world-finals"
    if re.search(r"Championship|Division", name):
        return "championship"
    if re.search(r"Qualifier|preliminar", name, re.I):
        return "qualifier"
    return "regional"


def sources():
    seen, page = [], 1  # pages are 1-indexed; page 0 repeats page 1
    while True:
        t = fetch("%s/problem-sources?page=%d" % (BASE, page))
        found = [urllib.parse.unquote(x) for x in re.findall(r'href="/problem-sources/([^"]+)"', t or "")]
        new = [x for x in found if x not in seen]
        if not new:
            return seen
        seen += new
        page += 1


def _table(m):
    """Render a table as one text line per row (cells often wrap their content in <p>)."""
    rows = []
    for tr in re.findall(r"<tr[^>]*>(.*?)</tr>", m.group(0), re.S):
        cells = [re.sub(r"\s+", " ", re.sub(r"<[^>]+>", "", c)).strip()
                 for c in re.findall(r"<t[dh][^>]*>(.*?)</t[dh]>", tr, re.S)]
        rows.append(" ".join(cells))
    return "\n\n<pre>" + "\n".join(rows) + "</pre>\n\n"


def text_of(fragment):
    """Crude HTML -> text that keeps paragraphs and TeX."""
    t = re.sub(r"<(script|style)[^>]*>.*?</\1>", "", fragment, flags=re.S)
    # Source line breaks mean nothing outside <pre>; keep table rows on one line.
    parts = re.split(r"(<pre[^>]*>.*?</pre>)", t, flags=re.S)
    t = "".join(x if x.startswith("<pre") else re.sub(r"\s+", " ", x) for x in parts)
    t = re.sub(r"<table.*?</table>", _table, t, flags=re.S)
    t = re.sub(r"<h[1-6][^>]*>(.*?)</h[1-6]>", r"\n\n## \1\n\n", t, flags=re.S)
    t = re.sub(r"<li[^>]*>", "\n- ", t)
    t = re.sub(r"</(p|div|tr|table|ul|ol|pre)>", "\n\n", t)
    t = re.sub(r"<[^>]+>", "", t)
    t = html.unescape(t)
    t = re.sub(r"[ \t]*\n[ \t]*", "\n", re.sub(r"[ \t]{2,}", " ", t))
    return re.sub(r"\n{3,}", "\n\n", t).strip()


def scrape_sources(con):
    for name in sources():
        y = re.search(r"(19|20)\d\d", name)
        if not y or int(y.group(0)) < MIN_YEAR or not INCLUDE.search(name) or EXCLUDE.search(name):
            continue
        url = "%s/problem-sources/%s" % (BASE, urllib.parse.quote(name))
        t = fetch(url) or ""
        cid = "kattis:" + name
        con.execute("INSERT OR IGNORE INTO contests(id, source, name, year, kind, url) VALUES (?,?,?,?,?,?)",
                    (cid, "kattis", name, int(y.group(0)), kind_of(name), url))
        n = 0
        for row in t.split("<tr")[1:]:
            m = re.search(r'href="/problems/([^"/]+)"[^>]*>\s*(.*?)\s*</a>', row, re.S)
            if not m:
                continue
            tds = [text_of(x) for x in re.findall(r"<td[^>]*>(.*?)</td>", row, re.S)]
            diff = re.findall(r"\d+\.\d+", tds[6]) if len(tds) > 6 else []
            num = lambda s: int(s) if s.isdigit() else None
            pid = "kattis:" + m.group(1)
            con.execute(
                "INSERT INTO problems(id, source, source_id, contest_id, title, url, year, src_difficulty, submits, accepted)"
                " VALUES (?,?,?,?,?,?,?,?,?,?) ON CONFLICT(id) DO UPDATE SET"
                " src_difficulty=excluded.src_difficulty, submits=excluded.submits, accepted=excluded.accepted",
                (pid, "kattis", m.group(1), cid, html.unescape(m.group(2)), "%s/problems/%s" % (BASE, m.group(1)),
                 int(y.group(0)), float(diff[-1]) if diff else None, num(tds[3]), num(tds[4])))
            n += 1
        con.commit()
        print("%3d  %s" % (n, name), flush=True)


def parse_problem(t):
    """Problem page HTML -> (statement, samples, time_limit_ms, memory_limit_mb)."""
    m = re.search(r'<div class="problembody">(.*?)</div>\s*</div>\s*</article>', t, re.S)
    body = m.group(1) if m else ""
    samples = []
    for tab in re.findall(r'<table class="sample".*?</table>', body, re.S):
        pres = [html.unescape(x) for x in re.findall(r"<pre>(.*?)</pre>", tab, re.S)]
        if len(pres) == 2:
            samples.append(pres)
    statement = text_of(re.sub(r'<table class="sample".*?</table>', "", body, flags=re.S))
    tl = re.search(r"CPU Time limit</span>\s*<span[^>]*>\s*([\d.]+)\s*second", t)
    ml = re.search(r"Memory limit</span>\s*<span[^>]*>\s*(\d+)\s*MB", t)
    return (statement, json.dumps(samples), int(float(tl.group(1)) * 1000) if tl else None,
            int(ml.group(1)) if ml else None)


def scrape_details(con, redo=False):
    """Fetch statements. redo=True re-parses already-downloaded pages from the cache."""
    rows = con.execute("SELECT id, source_id FROM problems WHERE source='kattis' AND statement IS %s"
                       % ("NOT NULL" if redo else "NULL")).fetchall()
    for i, r in enumerate(rows):
        try:
            t = fetch("%s/problems/%s" % (BASE, r["source_id"]), delay=1.0) or ""
        except Exception as e:
            print("skip %s: %s" % (r["id"], e), file=sys.stderr)
            continue
        con.execute("UPDATE problems SET statement=?, samples=?, time_limit_ms=?, memory_limit_mb=? WHERE id=?",
                    parse_problem(t) + (r["id"],))
        con.commit()  # per row: other scrapers write to the same database
        if i % 20 == 0:
            print("kattis details %d/%d" % (i, len(rows)), flush=True)


if __name__ == "__main__":
    con = connect()
    if "details" not in sys.argv and "rerender" not in sys.argv:
        scrape_sources(con)
    if "list" not in sys.argv:
        scrape_details(con, redo="rerender" in sys.argv)
