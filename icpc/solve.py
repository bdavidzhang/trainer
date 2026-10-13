"""Tools for the solving pass: show a problem, check a solution on samples, record an analysis.

    python3 -m icpc.solve show <id>
    python3 -m icpc.solve check <id> <solution.cpp>
    python3 -m icpc.solve record <analysis.json>
    python3 -m icpc.solve todo [--limit N] [--offset K]
"""
import json
import os
import subprocess
import sys
import tempfile

from .db import ROOT, connect
from .tags import TOPICS

SHIM = os.path.join(ROOT, "icpc", "shim")


def show(con, pid):
    r = con.execute("SELECT p.*, c.name contest FROM problems p LEFT JOIN contests c ON c.id=p.contest_id"
                    " WHERE p.id=?", (pid,)).fetchone()
    if not r:
        sys.exit("unknown problem " + pid)
    print("# %s  (%s)\ncontest: %s\nurl: %s\nlimits: %s ms, %s MB\nsource difficulty: %s  solved/attempted: %s/%s\n"
          % (r["title"], r["id"], r["contest"], r["url"], r["time_limit_ms"], r["memory_limit_mb"],
             r["src_difficulty"], r["accepted"], r["submits"]))
    print(r["statement"] or "(statement not downloaded)")
    for i, (a, b) in enumerate(json.loads(r["samples"] or "[]"), 1):
        print("\n--- sample input %d ---\n%s\n--- sample output %d ---\n%s" % (i, a.rstrip(), i, b.rstrip()))


def same(expected, got):
    a, b = expected.split(), got.split()
    if len(a) != len(b):
        return False
    for x, y in zip(a, b):
        if x == y:
            continue
        try:
            fx, fy = float(x), float(y)
        except ValueError:
            return False
        if abs(fx - fy) > 1e-6 * max(1.0, abs(fx)):
            return False
    return True


def check(con, pid, path):
    """Compile and run on the samples. Exit 0 only if every sample matches."""
    r = con.execute("SELECT samples, time_limit_ms FROM problems WHERE id=?", (pid,)).fetchone()
    samples = json.loads(r["samples"] or "[]")
    exe = os.path.join(tempfile.mkdtemp(), "sol")
    c = subprocess.run(["g++", "-std=c++17", "-O2", "-I", SHIM, "-o", exe, path], capture_output=True, text=True)
    if c.returncode:
        print("COMPILE ERROR\n" + c.stderr[-3000:])
        return 2
    if not samples:
        print("NO SAMPLES (compiled ok)")
        return 3
    ok = True
    for i, (inp, out) in enumerate(samples, 1):
        try:
            p = subprocess.run([exe], input=inp, capture_output=True, text=True,
                               timeout=max(2.0, 3 * (r["time_limit_ms"] or 2000) / 1000.0))
            verdict = "ok" if p.returncode == 0 and same(out, p.stdout) else ("RTE" if p.returncode else "WRONG")
        except subprocess.TimeoutExpired:
            p, verdict = None, "TIMEOUT"
        ok = ok and verdict == "ok"
        print("sample %d: %s" % (i, verdict))
        if verdict == "WRONG":
            print("  expected: %s\n  got:      %s" % (out.strip()[:400], p.stdout.strip()[:400]))
    return 0 if ok else 1


def record(con, path):
    """Store an analysis. JSON keys: id, rating, topics, key_idea, sketch, code_path, samples_passed."""
    a = json.load(open(path))
    for a in (a if isinstance(a, list) else [a]):
        bad = [t for t in a["topics"] if t not in TOPICS]
        if bad:
            sys.exit("%s: unknown topics %s (see icpc/tags.py)" % (a["id"], bad))
        if not con.execute("SELECT 1 FROM problems WHERE id=?", (a["id"],)).fetchone():
            sys.exit("unknown problem " + a["id"])
        con.execute("INSERT OR REPLACE INTO analyses(problem_id, rating, key_idea, sketch, code_path, samples_passed)"
                    " VALUES (?,?,?,?,?,?)", (a["id"], int(a["rating"]), a["key_idea"], a["sketch"],
                                              a.get("code_path"), int(bool(a.get("samples_passed")))))
        con.execute("DELETE FROM problem_tags WHERE problem_id=? AND origin='solver'", (a["id"],))
        for t in a["topics"]:
            con.execute("INSERT OR IGNORE INTO problem_tags VALUES (?,?,'solver')", (a["id"], t))
        print("recorded " + a["id"])
    con.commit()


def todo(con, limit, offset):
    """Unsolved, statement-ready problems, most relevant contests first."""
    rows = con.execute(
        "SELECT p.id FROM problems p JOIN contests c ON c.id=p.contest_id"
        " WHERE p.dup_of IS NULL AND p.statement != '' AND p.id NOT IN (SELECT problem_id FROM analyses)"
        " ORDER BY (c.kind='regional') DESC, p.year DESC, c.id, p.id LIMIT ? OFFSET ?", (limit, offset))
    for r in rows:
        print(r["id"])


def main():
    con, a = connect(), sys.argv[1:]
    if a[:1] == ["show"]:
        show(con, a[1])
    elif a[:1] == ["check"]:
        sys.exit(check(con, a[1], a[2]))
    elif a[:1] == ["record"]:
        record(con, a[1])
    elif a[:1] == ["todo"]:
        opt = dict(zip(a[1::2], a[2::2]))
        todo(con, int(opt.get("--limit", 20)), int(opt.get("--offset", 0)))
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main()
