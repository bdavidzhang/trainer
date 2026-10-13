"""SQLite schema and helpers for the ICPC training database."""
import os
import sqlite3

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DB_PATH = os.path.join(ROOT, "data", "icpc.db")

SCHEMA = """
CREATE TABLE IF NOT EXISTS contests (
    id TEXT PRIMARY KEY,          -- e.g. 'luogu:ICPC 2020 NAC', 'kattis:<source>', 'cfgym:106758'
    source TEXT NOT NULL,         -- luogu | kattis | cfgym
    name TEXT NOT NULL,
    year INTEGER,
    region TEXT,
    kind TEXT,                    -- regional | championship | world-finals | qualifier | other
    url TEXT
);
CREATE TABLE IF NOT EXISTS problems (
    id TEXT PRIMARY KEY,          -- 'luogu:P16001', 'kattis:convoy'
    source TEXT NOT NULL,
    source_id TEXT NOT NULL,
    contest_id TEXT REFERENCES contests(id),
    title TEXT NOT NULL,
    url TEXT,
    year INTEGER,
    statement TEXT,
    samples TEXT,                 -- JSON [[input, output], ...]
    time_limit_ms INTEGER,
    memory_limit_mb INTEGER,
    src_difficulty REAL,          -- luogu 1-7 (0 = unrated), kattis 1.0-10.0
    submits INTEGER,
    accepted INTEGER,
    est_rating INTEGER,           -- Codeforces-equivalent estimate from source stats
    dup_of TEXT                   -- id of the same problem from another source
);
CREATE TABLE IF NOT EXISTS problem_tags (
    problem_id TEXT NOT NULL REFERENCES problems(id),
    tag TEXT NOT NULL,
    origin TEXT NOT NULL,         -- luogu | solver
    PRIMARY KEY (problem_id, tag, origin)
);
CREATE TABLE IF NOT EXISTS analyses (
    problem_id TEXT PRIMARY KEY REFERENCES problems(id),
    rating INTEGER,               -- solver's Codeforces-equivalent rating
    key_idea TEXT,
    sketch TEXT,
    code_path TEXT,
    samples_passed INTEGER,       -- 1 if the solution passed all samples locally
    created TEXT DEFAULT CURRENT_TIMESTAMP
);
CREATE TABLE IF NOT EXISTS progress (
    problem_id TEXT PRIMARY KEY REFERENCES problems(id),
    status TEXT NOT NULL,         -- solved | upsolved | failed | skipped
    minutes INTEGER,
    notes TEXT,
    ts TEXT DEFAULT CURRENT_TIMESTAMP
);
CREATE INDEX IF NOT EXISTS idx_problems_contest ON problems(contest_id);
CREATE INDEX IF NOT EXISTS idx_tags_tag ON problem_tags(tag);
"""


def connect():
    os.makedirs(os.path.dirname(DB_PATH), exist_ok=True)
    con = sqlite3.connect(DB_PATH, timeout=120)
    con.row_factory = sqlite3.Row
    con.execute("PRAGMA journal_mode=WAL")
    con.executescript(SCHEMA)
    return con
