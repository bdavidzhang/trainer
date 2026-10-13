#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) { int a, b; scanf("%d %d", &a, &b); g[a].push_back(b); g[b].push_back(a); }
    vector<int> col(n + 1, 0);
    for (int s = 1; s <= n; s++) if (!col[s]) {
        int cnt = 0;
        vector<int> q{s}; col[s] = 1; cnt = 1;
        for (size_t i = 0; i < q.size(); i++)
            for (int v : g[q[i]]) if (!col[v]) { col[v] = cnt % k + 1; cnt++; q.push_back(v); }
        if (cnt < k) { puts("impossible"); return 0; }
    }
    for (int i = 1; i <= n; i++) printf("%d%c", col[i], i == n ? '\n' : ' ');
}
