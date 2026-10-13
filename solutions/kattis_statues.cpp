#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<int>> g(n, vector<int>(m));
    vector<int> hs;
    for (auto& r : g) for (int& v : r) { scanf("%d", &v); if (v > 0) hs.push_back(v); }
    sort(hs.begin(), hs.end());
    int best = INT_MAX;
    for (int c = 0; c < 4; c++) {
        auto dg = [&](int i, int j) { return ((c & 1) ? n - 1 - i : i) + ((c & 2) ? m - 1 - j : j); };
        vector<int> cnt(n + m, 0);
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (g[i][j] > 0) cnt[dg(i, j)]++;
        vector<int> target(hs.size());
        int r = 0;
        for (int d = 0; d < n + m; d++) for (int k = 0; k < cnt[d]; k++) target[r++] = d;
        int moved = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (g[i][j] > 0) {
            int rk = lower_bound(hs.begin(), hs.end(), g[i][j]) - hs.begin();
            if (target[rk] != dg(i, j)) moved++;
        }
        best = min(best, moved);
    }
    printf("%d\n", best);
}
