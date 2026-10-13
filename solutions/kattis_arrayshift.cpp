#include <bits/stdc++.h>
using namespace std;
// b_j = product of a[j..j+k] (a beyond n is 0). With w = k+1 and m = n-k real windows:
// each window is either 0 (contains a zero) or 2^c (no zero, c twos); c <= w is recoverable
// because 2 has huge order mod 1e9+7.
int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<long long> b(n + 1); for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
    const long long MOD = 1000000007LL; int w = k + 1, m = n - k;
    unordered_map<long long, int> lg; lg.reserve(2 * w + 8);
    { long long p = 1; for (int c = 0; c <= w; c++) { lg[p] = c; p = p * 2 % MOD; } }
    for (int j = m + 1; j <= n; j++) if (b[j] != 0) { puts("-1"); return 0; }
    vector<int> c(m + 2, -1); // -1 = zero window
    for (int j = 1; j <= m; j++) if (b[j] != 0) {
        auto it = lg.find(b[j]); if (it == lg.end()) { puts("-1"); return 0; }
        c[j] = it->second;
    }
    // positions covered by a nonzero window must be nonzero; all others become 0
    vector<int> cov(n + 2, 0);
    for (int j = 1; j <= m; j++) if (c[j] >= 0) { cov[j]++; cov[j + w]--; }
    vector<int> a(n + 1, 0), pz(n + 1, 0);
    for (int i = 1; i <= n; i++) { cov[i] += cov[i - 1]; pz[i] = pz[i - 1] + (cov[i] == 0); }
    for (int j = 1; j <= m; j++) if (c[j] < 0 && pz[j + w - 1] - pz[j - 1] == 0) { puts("-1"); return 0; }
    // each maximal run of nonzero windows j..e: t[i+w] = t[i] + (c[i+1]-c[i]) along chains mod w
    for (int j = 1; j <= m;) {
        if (c[j] < 0) { j++; continue; }
        int e = j; while (e + 1 <= m && c[e + 1] >= 0) e++;
        vector<int> freeStart; int forcedOnes = 0;
        for (int st = j; st <= j + w - 1; st++) {
            // chain st, st+w, ... ; step i -> i+w exists while i <= e-1
            int first = -1; // value forced at st, or -1 if free
            int cur = -1;
            for (int i = st; i <= e - 1; i += w) {
                int d = c[i + 1] - c[i];
                if (d > 1 || d < -1) { puts("-1"); return 0; }
                if (cur == -1) {
                    if (d == 0) continue;
                    cur = (d == 1) ? 1 : 0; // value at i+w
                    first = 1 - cur;        // value at i, equal to value at st
                } else {
                    cur += d; if (cur < 0 || cur > 1) { puts("-1"); return 0; }
                }
            }
            if (first == -1) freeStart.push_back(st);
            else {
                forcedOnes += first;
                int v = first; a[st] = v + 1;
                for (int i = st; i <= e - 1; i += w) { v += c[i + 1] - c[i]; a[i + w] = v + 1; }
            }
        }
        int need = c[j] - forcedOnes;
        if (need < 0 || need > (int)freeStart.size()) { puts("-1"); return 0; }
        for (size_t q = 0; q < freeStart.size(); q++) {
            int v = ((int)q < need) ? 2 : 1, st = freeStart[q];
            a[st] = v;
            for (int i = st; i <= e - 1; i += w) a[i + w] = v;
        }
        j = e + 1;
    }
    for (int i = 1; i <= n; i++) printf("%d%c", a[i], i == n ? '\n' : ' ');
}
