"""ICPC regional trainer.

    python3 -m icpc.trainer stats
    python3 -m icpc.trainer topics
    python3 -m icpc.trainer list [--topic T] [--min R] [--max R] [--year Y] [--contest TEXT] [--all] [-n N]
    python3 -m icpc.trainer recommend [--rating 2000] [-n 8]
    python3 -m icpc.trainer contests [--year Y] [--kind regional]
    python3 -m icpc.trainer contest "<contest name fragment>"
    python3 -m icpc.trainer show <id> [--spoil]
    python3 -m icpc.trainer mark <id> solved|upsolved|failed|skipped [--minutes M] [--notes TEXT]
"""
import argparse
import random

from .db import connect

# One row per unique problem with its best rating (solver's if analysed, else source estimate).
VIEW = """
SELECT p.id, p.title, p.url, p.year, c.name contest, c.kind,
       COALESCE(a.rating, p.est_rating) rating, a.rating IS NOT NULL analysed,
       (SELECT group_concat(DISTINCT tag) FROM problem_tags t WHERE t.problem_id=p.id) tags,
       g.status
FROM problems p JOIN contests c ON c.id=p.contest_id
LEFT JOIN analyses a ON a.problem_id=p.id
LEFT JOIN progress g ON g.problem_id=p.id
WHERE p.dup_of IS NULL
"""


def table(rows):
    """Print problems as an aligned table; '~' marks a rating that is only a source estimate."""
    head = ("ID", "Rating", "Status", "Title", "Contest", "Topics", "Link")
    body = [(r["id"], "%s%s" % (r["rating"] or "?", "" if r["analysed"] else "~"), r["status"] or "",
             r["title"][:40], r["contest"][:44], (r["tags"] or "").replace(",", ", "), r["url"] or "") for r in rows]
    if not body:
        print("(no problems match)")
        return
    width = [max(len(x[i]) for x in [head] + body) for i in range(len(head))]
    line = lambda cells: "| " + " | ".join(c.ljust(w) for c, w in zip(cells, width)) + " |"
    print(line(head))
    print("|" + "|".join("-" * (w + 2) for w in width) + "|")
    for cells in body:
        print(line(cells))


def cmd_stats(con, a):
    print("problems: %d unique (%d analysed), contests: %d" % (
        con.execute("SELECT count(*) FROM problems WHERE dup_of IS NULL").fetchone()[0],
        con.execute("SELECT count(*) FROM analyses").fetchone()[0],
        con.execute("SELECT count(*) FROM contests WHERE id IN (SELECT contest_id FROM problems)").fetchone()[0]))
    print("\nyour progress by topic (solved+upsolved / attempted):")
    q = ("SELECT t.tag, sum(g.status IN ('solved','upsolved')) ok, sum(g.status='solved') clean, count(*) n"
         " FROM progress g JOIN (SELECT DISTINCT problem_id, tag FROM problem_tags) t ON t.problem_id=g.problem_id"
         " WHERE g.status != 'skipped' GROUP BY t.tag ORDER BY n DESC")
    for r in con.execute(q):
        print("  %-24s %d/%d  (%d in contest time)" % (r["tag"], r["ok"], r["n"], r["clean"]))
    for r in con.execute("SELECT status, count(*) n FROM progress GROUP BY status"):
        print("%s: %d" % (r["status"], r["n"]))


def cmd_topics(con, a):
    q = ("SELECT tag, count(DISTINCT problem_id) n FROM problem_tags"
         " WHERE problem_id IN (SELECT id FROM problems WHERE dup_of IS NULL) GROUP BY tag ORDER BY n DESC")
    for r in con.execute(q):
        print("%-24s %d" % (r["tag"], r["n"]))


def cmd_list(con, a):
    q, args = VIEW, []
    if a.topic:
        q += " AND p.id IN (SELECT problem_id FROM problem_tags WHERE tag=?)"
        args.append(a.topic)
    if a.min:
        q += " AND COALESCE(a.rating, p.est_rating) >= ?"
        args.append(a.min)
    if a.max:
        q += " AND COALESCE(a.rating, p.est_rating) <= ?"
        args.append(a.max)
    if a.year:
        q += " AND p.year = ?"
        args.append(a.year)
    if a.contest:
        q += " AND c.name LIKE ?"
        args.append("%" + a.contest + "%")
    if not a.all:
        q += " AND g.status IS NULL"
    table(con.execute(q + " ORDER BY rating, p.year DESC LIMIT ?", args + [a.n]).fetchall())


def cmd_recommend(con, a):
    """Unsolved problems around your level, weighted toward topics you fail or have not touched."""
    weak = {}
    for r in con.execute("SELECT t.tag, avg(g.status IN ('failed','upsolved')) f, count(*) n FROM progress g"
                         " JOIN (SELECT DISTINCT problem_id, tag FROM problem_tags) t ON t.problem_id=g.problem_id"
                         " WHERE g.status != 'skipped' GROUP BY t.tag"):
        weak[r["tag"]] = (r["f"], r["n"])
    rows = con.execute(VIEW + " AND g.status IS NULL AND c.kind IN ('regional','championship')"
                       " AND COALESCE(a.rating, p.est_rating) BETWEEN ? AND ?",
                       (a.rating - 200, a.rating + 400)).fetchall()

    def weight(r):
        w = 2.0 if r["analysed"] else 1.0
        for t in (r["tags"] or "").split(","):
            f, n = weak.get(t, (0.5, 0))
            w *= 1.0 + f + (0.5 if n < 3 else 0.0)
        return w * random.random()

    table(sorted(sorted(rows, key=weight, reverse=True)[:a.n], key=lambda r: r["rating"]))


def cmd_contests(con, a):
    q = ("SELECT c.name, c.year, c.kind, count(*) n, sum(g.status IS NOT NULL) done,"
         " min(COALESCE(x.rating, p.est_rating)) lo, max(COALESCE(x.rating, p.est_rating)) hi"
         " FROM contests c JOIN problems p ON p.contest_id=c.id LEFT JOIN progress g ON g.problem_id=p.id"
         " LEFT JOIN analyses x ON x.problem_id=p.id WHERE c.kind LIKE ? AND (? IS NULL OR c.year=?)"
         " GROUP BY c.id HAVING n >= 8 ORDER BY c.year DESC, c.name")
    for r in con.execute(q, (a.kind or "%", a.year, a.year)):
        print("%d  %-13s %2d problems  %2d done  %s-%s  %s" % (
            r["year"], r["kind"], r["n"], r["done"], r["lo"], r["hi"], r["name"]))


def cmd_contest(con, a):
    table(con.execute("SELECT * FROM (" + VIEW.replace("WHERE p.dup_of IS NULL", "WHERE 1") +
                      ") WHERE contest LIKE ? ORDER BY contest, rating", ("%" + a.name + "%",)).fetchall())


def cmd_show(con, a):
    r = con.execute("SELECT * FROM (" + VIEW.replace("WHERE p.dup_of IS NULL", "WHERE 1") + ") WHERE id=?",
                    (a.id,)).fetchone()
    if not r:
        raise SystemExit("unknown problem " + a.id)
    p = con.execute("SELECT statement FROM problems WHERE id=?", (a.id,)).fetchone()
    print("%s  [%s]\n%s (%s)\n%s\nrating: %s%s\n" % (r["title"], r["id"], r["contest"], r["year"], r["url"],
                                                    r["rating"], "" if r["analysed"] else " (source estimate)"))
    print(p["statement"] or "(statement not downloaded)")
    if a.spoil:
        x = con.execute("SELECT * FROM analyses WHERE problem_id=?", (a.id,)).fetchone()
        print("\ntopics: %s" % r["tags"])
        if x:
            print("key idea: %s\n\n%s\n\nreference code: %s (%s)" % (
                x["key_idea"], x["sketch"], x["code_path"],
                "passes samples" if x["samples_passed"] else "NOT verified on samples"))


def cmd_mark(con, a):
    if not con.execute("SELECT 1 FROM problems WHERE id=?", (a.id,)).fetchone():
        raise SystemExit("unknown problem " + a.id)
    con.execute("INSERT OR REPLACE INTO progress(problem_id, status, minutes, notes) VALUES (?,?,?,?)",
                (a.id, a.status, a.minutes, a.notes))
    con.commit()
    print("%s -> %s" % (a.id, a.status))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("stats")
    sub.add_parser("topics")
    s = sub.add_parser("list")
    s.add_argument("--topic"); s.add_argument("--min", type=int); s.add_argument("--max", type=int)
    s.add_argument("--year", type=int); s.add_argument("--contest"); s.add_argument("--all", action="store_true")
    s.add_argument("-n", type=int, default=30)
    s = sub.add_parser("recommend")
    s.add_argument("--rating", type=int, default=2000); s.add_argument("-n", type=int, default=8)
    s = sub.add_parser("contests")
    s.add_argument("--year", type=int); s.add_argument("--kind")
    s = sub.add_parser("contest"); s.add_argument("name")
    s = sub.add_parser("show"); s.add_argument("id"); s.add_argument("--spoil", action="store_true")
    s = sub.add_parser("mark"); s.add_argument("id")
    s.add_argument("status", choices=["solved", "upsolved", "failed", "skipped"])
    s.add_argument("--minutes", type=int); s.add_argument("--notes")
    a = ap.parse_args()
    globals()["cmd_" + a.cmd](connect(), a)


if __name__ == "__main__":
    main()
