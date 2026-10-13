# ICPC regional trainer

A local database of ICPC regional-level problems from 2016 onward, with difficulty
ratings, topic tags and solution notes, plus a small CLI for training.

## Data

| Source | What | Notes |
|---|---|---|
| Kattis | North American regionals (Mid-Central, NCNA, ECNA, ...), NAQ, NAC, NWERC, NCPC, BAPC, GCPC, UKIEPC, Vietnam, World Finals | statements, samples, Kattis difficulty, solve counts |
| Luogu | ICPC-tagged problems: Asian regionals, NERC, SWERC, CERC, SEERC, LAC, EC Final, NAC, WF | statements, samples, difficulty level, community topic tags |
| Codeforces Gym | Official ICPC contest index only | links for virtual contests; problems need a login |

Everything lives in `data/icpc.db` (SQLite): `contests`, `problems`, `problem_tags`,
`analyses` (solver rating, key idea, sketch, reference code) and `progress` (yours).
Problems on both Kattis and Luogu are linked through `problems.dup_of`.

Ratings are Codeforces-equivalent. `~` after a rating in the CLI means it is only an
estimate from the source site's difficulty; without it, the problem has been solved
and rated in the solving pass (`analyses`), with reference code in `solutions/`.

## Rebuild

    python3 -m icpc.scrape_luogu      # list, then statements (slow, cached in data/cache)
    python3 -m icpc.scrape_kattis
    python3 -m icpc.scrape_cfgym
    python3 -m icpc.enrich            # canonical tags, rating estimates, duplicates

## Train

    python3 -m icpc.trainer recommend --rating 2000     # picks near your level, biased to weak topics
    python3 -m icpc.trainer contests --kind regional    # full sets for 5-hour virtuals
    python3 -m icpc.trainer contest "Mid-Central"
    python3 -m icpc.trainer list --topic flows --min 1800 --max 2400
    python3 -m icpc.trainer show kattis:waif            # add --spoil for idea, sketch, code
    python3 -m icpc.trainer mark kattis:waif solved --minutes 35
    python3 -m icpc.trainer stats

## Solving pass

    python3 -m icpc.solve todo --limit 20               # next unanalysed problems
    python3 -m icpc.solve show <id>
    python3 -m icpc.solve check <id> solutions/<name>.cpp
    python3 -m icpc.solve record analysis/<name>.json

Reference solutions are checked against the published samples only, not the hidden
tests; treat them as strong hints, not accepted submissions.
