"""Scrape ICPC-tagged problems from Luogu (list pages, then statements)."""
import json
import re
import sys

from .db import connect
from .http import fetch

BASE = "https://www.luogu.com.cn"
ICPC_TAG = 335
MIN_YEAR = 2016
CTX = re.compile(r'<script id="lentille-context" type="application/json">(.*?)</script>', re.S)


def context(html):
    m = CTX.search(html or "")
    return json.loads(m.group(1)) if m else None


def split_title(name):
    """'[ICPC 2020 NAC] ICPC Camp' -> ('ICPC 2020 NAC', 2020, 'ICPC Camp')."""
    m = re.match(r"\s*\[([^\]]+)\]\s*(.*)", name)
    if not m:
        return None, None, name
    y = re.search(r"(19|20)\d\d", m.group(1))
    return m.group(1).strip(), int(y.group(0)) if y else None, m.group(2).strip()


def kind_of(contest):
    c = contest.upper()
    if re.search(r"\bWF\b", c):
        return "world-finals"
    if re.search(r"\b(NAC|EC ?FINAL|NERC|NEERC|SWERC|CERC|SEERC|NWERC)\b", c):
        return "championship" if re.search(r"NAC|EC ?FINAL", c) else "regional"
    if "ONLINE" in c or "网络" in contest or "QUAL" in c:
        return "qualifier"
    return "regional"


def scrape_list(con):
    page, total = 1, None
    while True:
        d = context(fetch("%s/problem/list?type=P&tag=%d&page=%d" % (BASE, ICPC_TAG, page)))
        probs = d["data"]["problems"]
        total = probs["count"]
        if not probs["result"]:
            break
        for p in probs["result"]:
            contest, year, title = split_title(p["name"])
            if not contest or not year or year < MIN_YEAR:
                continue
            cid = "luogu:" + contest
            con.execute("INSERT OR IGNORE INTO contests(id, source, name, year, kind, url) VALUES (?,?,?,?,?,?)",
                        (cid, "luogu", contest, year, kind_of(contest), None))
            pid = "luogu:" + p["pid"]
            con.execute(
                "INSERT INTO problems(id, source, source_id, contest_id, title, url, year, src_difficulty, submits, accepted)"
                " VALUES (?,?,?,?,?,?,?,?,?,?) ON CONFLICT(id) DO UPDATE SET"
                " src_difficulty=excluded.src_difficulty, submits=excluded.submits, accepted=excluded.accepted",
                (pid, "luogu", p["pid"], cid, title, "%s/problem/%s" % (BASE, p["pid"]), year,
                 p["difficulty"], p["totalSubmit"], p["totalAccepted"]))
            con.execute("DELETE FROM problem_tags WHERE problem_id=? AND origin='luogu'", (pid,))
            for t in p["tags"]:
                con.execute("INSERT OR IGNORE INTO problem_tags VALUES (?,?,?)", (pid, "lg:%d" % t, "luogu"))
        con.commit()
        if page * probs["perPage"] >= total:
            break
        page += 1
    print("luogu list: %d ICPC problems total on site" % total)


def english(part):
    return sum(ord(c) < 128 for c in part) > 0.9 * max(1, len(part))


def render(c):
    out = []
    for key, head in (("background", "Background"), ("description", None), ("formatI", "Input"),
                      ("formatO", "Output"), ("hint", "Notes")):
        v = (c.get(key) or "").strip()
        if v:
            out.append(("## %s\n\n" % head if head else "") + v)
    return "\n\n".join(out)


def scrape_details(con):
    rows = con.execute("SELECT id, source_id FROM problems WHERE source='luogu' AND statement IS NULL").fetchall()
    for i, r in enumerate(rows):
        try:
            d = context(fetch("%s/problem/%s" % (BASE, r["source_id"]), delay=1.2))
            p = d["data"]["problem"]
        except Exception as e:
            print("skip %s: %s" % (r["id"], e), file=sys.stderr)
            continue
        texts = [render(c) for c in (p.get("content"), p.get("contenu")) if c]
        texts.sort(key=lambda t: (not english(t), -len(t)))
        lim = p.get("limits") or {}
        con.execute("UPDATE problems SET statement=?, samples=?, time_limit_ms=?, memory_limit_mb=? WHERE id=?",
                    (texts[0] if texts else "", json.dumps(p.get("samples") or []),
                     max(lim.get("time") or [0]) or None, (max(lim.get("memory") or [0]) // 1024) or None, r["id"]))
        con.commit()  # per row: other scrapers write to the same database
        if i % 20 == 0:
            print("luogu details %d/%d" % (i, len(rows)), flush=True)
    con.commit()


if __name__ == "__main__":
    con = connect()
    if "details" not in sys.argv:
        scrape_list(con)
    if "list" not in sys.argv:
        scrape_details(con)
