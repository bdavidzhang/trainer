"""Post-scrape pass: canonical tags, rating estimates, cross-source duplicates."""
import re

from .db import connect
from .tags import LUOGU

# Luogu difficulty level (1-8) -> rough Codeforces rating.
LUOGU_RATING = {1: 800, 2: 1000, 3: 1200, 4: 1500, 5: 1800, 6: 2100, 7: 2500, 8: 3000}


def kattis_rating(d):
    return int(round((800 + (d - 1.0) * 270) / 50.0) * 50)


def norm(title):
    return re.sub(r"[^a-z0-9]", "", title.lower())


def main():
    con = connect()
    for r in con.execute("SELECT problem_id, tag FROM problem_tags WHERE tag LIKE 'lg:%'").fetchall():
        topic = LUOGU.get(int(r["tag"][3:]))
        if topic:
            con.execute("INSERT OR IGNORE INTO problem_tags VALUES (?,?,'luogu')", (r["problem_id"], topic))
    con.execute("DELETE FROM problem_tags WHERE tag LIKE 'lg:%'")

    for r in con.execute("SELECT id, source, src_difficulty d FROM problems").fetchall():
        est = None
        if r["source"] == "luogu" and r["d"]:
            est = LUOGU_RATING.get(int(r["d"]))
        elif r["source"] == "kattis" and r["d"]:
            est = kattis_rating(r["d"])
        con.execute("UPDATE problems SET est_rating=? WHERE id=?", (est, r["id"]))

    # Same problem on both sites: keep the Kattis copy (English judge), carry Luogu's tags over.
    kattis = {}
    for r in con.execute("SELECT id, title, year FROM problems WHERE source='kattis'"):
        kattis.setdefault(norm(r["title"]), []).append(r)
    dups = 0
    for r in con.execute("SELECT id, title, year FROM problems WHERE source='luogu'").fetchall():
        key = norm(r["title"])
        match = [k for k in kattis.get(key, []) if len(key) >= 5 and abs(k["year"] - r["year"]) <= 1]
        if match:
            con.execute("UPDATE problems SET dup_of=? WHERE id=?", (match[0]["id"], r["id"]))
            con.execute("INSERT OR IGNORE INTO problem_tags SELECT ?, tag, origin FROM problem_tags WHERE problem_id=?",
                        (match[0]["id"], r["id"]))
            dups += 1
    con.commit()
    print("enriched; %d luogu problems are duplicates of kattis ones" % dups)


if __name__ == "__main__":
    main()
