#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int c[305][305];
long long C[305][305], pre[305][305], p2[305];
int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) scanf("%d", &c[i][j]);
    for (int i = 0; i <= 300; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        long long s = 0;
        for (int j = 0; j <= 300; j++) { s = (s + C[i][j]) % MOD; pre[i][j] = s; }
    }
    p2[0] = 1; for (int i = 1; i <= 300; i++) p2[i] = p2[i - 1] * 2 % MOD;
    // peel order: a vertex whose edges to all remaining vertices share one colour always exists
    vector<int> alive(n); iota(alive.begin(), alive.end(), 0);
    vector<int> seq; // colours in peel order (last vertex has none)
    while (alive.size() > 1) {
        int found = -1, col = 0;
        for (int idx = 0; idx < (int)alive.size() && found < 0; idx++) {
            int v = alive[idx]; int cc = -1; bool ok = true;
            for (int u : alive) if (u != v) { if (cc < 0) cc = c[v][u]; else if (c[v][u] != cc) { ok = false; break; } }
            if (ok) { found = idx; col = cc; }
        }
        if (found < 0) { found = 0; col = c[alive[0]][alive[1]]; } // cannot happen on valid input
        seq.push_back(col);
        alive.erase(alive.begin() + found);
    }
    vector<int> cnt(301, 0);
    long long ans = 0;
    for (int p = 0; p < n; p++) {
        // vertex p is the last chosen vertex; subsets of first p vertices with colour counts cnt
        long long tot = p2[p];
        ans = (ans + tot) % MOD;
        int mx = 0; vector<int> present;
        for (int k = 1; k <= 300; k++) if (cnt[k]) { present.push_back(cnt[k]); mx = max(mx, cnt[k]); }
        for (int t = 0; t < mx; t++) {
            long long prod = 1;
            for (int a : present) prod = prod * pre[a][t] % MOD;
            ans = (ans + tot - prod + MOD) % MOD;
        }
        if (p < n - 1) cnt[seq[p]]++;
    }
    printf("%lld\n", ans % MOD);
}
