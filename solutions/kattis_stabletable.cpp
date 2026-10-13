#include <bits/stdc++.h>
using namespace std;
int main() {
    int h, w;
    scanf("%d %d", &h, &w);
    vector<vector<int>> g(h, vector<int>(w));
    int P = 0;
    for (auto& r : g) for (int& v : r) { scanf("%d", &v); P = max(P, v); }
    int F = 0; // floor node
    vector<vector<int>> adj(P + 1), radj(P + 1);
    auto add = [&](int a, int b) { adj[a].push_back(b); radj[b].push_back(a); };
    for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) {
        if (i == h - 1) add(g[i][j], F);
        else if (g[i][j] != g[i + 1][j]) add(g[i][j], g[i + 1][j]);
    }
    const int INF = 1e9;
    auto bfs = [&](int s, vector<vector<int>>& A) {
        vector<int> d(P + 1, INF);
        deque<int> q; d[s] = 0; q.push_back(s);
        while (!q.empty()) {
            int u = q.front(); q.pop_front();
            for (int v : A[u]) if (d[v] == INF) { d[v] = d[u] + 1; q.push_back(v); }
        }
        return d;
    };
    int t1 = g[0][0], t2 = g[0][0];
    for (int j = 0; j < w; j++) if (g[0][j] != t1) t2 = g[0][j];
    vector<int> d1 = bfs(t1, adj), d2 = bfs(t2, adj), df = bfs(F, radj);
    int best = INF;
    for (int v = 0; v <= P; v++) if (d1[v] < INF && d2[v] < INF && df[v] < INF) best = min(best, d1[v] + d2[v] + df[v]);
    printf("%d\n", best);
}
