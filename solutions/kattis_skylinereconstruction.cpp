#include <bits/stdc++.h>
using namespace std;
// C(l,r) = sum s_i * (i-l+1) * (r-i+1).  Known prefix p, query [p+1-M, p+k]:
// unknown bit j (1..k) has weight (M+j)*(k+1-j); the known part is subtracted.
// For each (k,M) the expected number of bits (common low prefix of the collision
// class of a random mask) is precomputed; the best pair is used each step.
static const int N = 2025, KMAX = 10, MMAX = 160;
#ifdef LOCAL
static string hidden; static int qcnt;
static long long ask(int l, int r) {
    qcnt++; long long c = 0;
    for (int i = l; i <= r; i++) if (hidden[i - 1] == '1') c += (long long)(i - l + 1) * (r - i + 1);
    return c;
}
#else
static long long ask(int l, int r) {
    printf("? %d %d\n", l, r); fflush(stdout);
    long long c; if (scanf("%lld", &c) != 1 || c < 0) exit(0);
    return c;
}
#endif
static void sums(int k, int M, vector<long long>& s) {
    s.assign(1 << k, 0);
    for (int j = 1; j <= k; j++) {
        long long w = (long long)(M + j) * (k + 1 - j); int h = 1 << (j - 1);
        for (int t = 0; t < h; t++) s[t + h] = s[t] + w;
    }
}
static double ev[KMAX + 1][MMAX + 1]; static int bestM[KMAX + 1][MMAX + 1];
static void precompute() {
    vector<long long> s;
    for (int k = 1; k <= KMAX; k++) for (int M = 0; M <= MMAX; M++) {
        sums(k, M, s);
        vector<int> id(1 << k); iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](int a, int b) { return s[a] < s[b]; });
        long long tot = 0, stall = 0;
        for (size_t i = 0; i < id.size();) {
            size_t j = i; int diff = 0;
            while (j < id.size() && s[id[j]] == s[id[i]]) { diff |= id[j] ^ id[i]; j++; }
            int pre = diff ? __builtin_ctz(diff) : k;
            tot += (long long)pre * (j - i); if (!pre) stall += j - i; i = j;
        }
        // bits per query, charging one extra query for every stall (unless injective)
        double e = (double)tot / ((1 << k) + stall);
        ev[k][M] = e; bestM[k][M] = M;
        if (M > 0 && ev[k][M - 1] >= e) { ev[k][M] = ev[k][M - 1]; bestM[k][M] = bestM[k][M - 1]; }
    }
}
static string solve() {
    vector<long long> s;
    vector<int> a(N + 2, 0); int p = 0; bool exact = false;
    while (p < N) {
        int bk = 1, bm = 0; double be = -1;
        for (int k = 1; k <= KMAX && p + k <= N; k++) {
            int cap = min(p, MMAX);
            if (exact && ev[k][cap] < k - 1e-9) continue; // after a stalled query use an injective window
            if (ev[k][cap] > be + 1e-12) { be = ev[k][cap]; bk = k; bm = bestM[k][cap]; }
        }
        int l = p + 1 - bm, r = p + bk;
        long long c = ask(l, r);
        for (int i = l; i <= p; i++) if (a[i]) c -= (long long)(i - l + 1) * (r - i + 1);
        sums(bk, bm, s);
        int first = -1, diff = 0;
        for (int m = 0; m < (1 << bk); m++) if (s[m] == c) { if (first < 0) first = m; else diff |= m ^ first; }
        if (first < 0) exit(0);
        int pre = diff ? __builtin_ctz(diff) : bk;
        for (int j = 1; j <= pre; j++) a[p + j] = (first >> (j - 1)) & 1;
        p += pre; exact = (pre == 0);
    }
    string res(N, '0'); for (int i = 1; i <= N; i++) if (a[i]) res[i - 1] = '1';
    return res;
}
int main() {
    precompute();
#ifdef LOCAL
    mt19937 rng(12345); int worst = 0; long long total = 0; int T = 1000;
    for (int t = 0; t < T; t++) {
        hidden.assign(N, '0'); for (auto& ch : hidden) ch = '0' + (rng() & 1);
        if (t == 0) hidden.assign(N, '0'); if (t == 1) hidden.assign(N, '1');
        qcnt = 0; string r = solve();
        if (r != hidden) { puts("WRONG"); return 1; }
        worst = max(worst, qcnt); total += qcnt;
    }
    printf("worst %d avg %.2f\n", worst, (double)total / T);
#else
    string r = solve(); printf("! %s\n", r.c_str()); fflush(stdout);
#endif
}
