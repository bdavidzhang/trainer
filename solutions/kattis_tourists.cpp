#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) { int a, b; scanf("%d %d", &a, &b); g[a].push_back(b); g[b].push_back(a); }
    const int LG = 18;
    vector<array<int, LG>> up(n + 1);
    vector<int> dep(n + 1, 0), order; order.reserve(n);
    vector<char> seen(n + 1, 0);
    order.push_back(1); seen[1] = 1; up[1].fill(1);
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (int w : g[v]) if (!seen[w]) {
            seen[w] = 1; dep[w] = dep[v] + 1; up[w][0] = v;
            for (int j = 1; j < LG; j++) up[w][j] = up[up[w][j - 1]][j - 1];
            order.push_back(w);
        }
    }
    auto lca = [&](int a, int b) {
        if (dep[a] < dep[b]) swap(a, b);
        int d = dep[a] - dep[b];
        for (int j = 0; j < LG; j++) if (d >> j & 1) a = up[a][j];
        if (a == b) return a;
        for (int j = LG - 1; j >= 0; j--) if (up[a][j] != up[b][j]) { a = up[a][j]; b = up[b][j]; }
        return up[a][0];
    };
    long long ans = 0;
    for (int x = 1; x <= n; x++) for (int y = 2 * x; y <= n; y += x) {
        int l = lca(x, y);
        ans += dep[x] + dep[y] - 2 * dep[l] + 1;
    }
    printf("%lld\n", ans);
}
