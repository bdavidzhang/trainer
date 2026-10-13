"""Index official ICPC contests in Codeforces Gym (metadata only).

Gym statements and standings need a logged-in session or API key, so problems
are not scraped; the contests are listed for virtual participation.
"""
import json

from .db import connect
from .http import fetch

MIN_YEAR = 2016


def main():
    con = connect()
    data = json.loads(fetch("https://codeforces.com/api/contest.list?gym=true", refresh=True))
    n = 0
    for c in data["result"]:
        season = c.get("season") or ""
        if c.get("kind") != "Official ICPC Contest" or not season[:4].isdigit() or int(season[:4]) < MIN_YEAR:
            continue
        con.execute("INSERT OR REPLACE INTO contests(id, source, name, year, region, kind, url) VALUES (?,?,?,?,?,?,?)",
                    ("cfgym:%d" % c["id"], "cfgym", c["name"], int(season[:4]),
                     c.get("icpcRegion") or c.get("country"), "regional", "https://codeforces.com/gym/%d" % c["id"]))
        n += 1
    con.commit()
    print("cfgym: %d official ICPC contests indexed" % n)


if __name__ == "__main__":
    main()
