#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Dinic {
    struct E { int to; ll cap; };
    vector<E> es; vector<vector<int>> g; vector<int> lvl, it;
    Dinic(int n) : g(n), lvl(n), it(n) {}
    void add(int a, int b, ll c) { g[a].push_back(es.size()); es.push_back({b, c}); g[b].push_back(es.size()); es.push_back({a, 0}); }
    bool bfs(int s, int t) {
        fill(lvl.begin(), lvl.end(), -1); lvl[s] = 0; vector<int> q{s};
        for (size_t i = 0; i < q.size(); i++) { int v = q[i]; for (int id : g[v]) if (es[id].cap > 0 && lvl[es[id].to] < 0) { lvl[es[id].to] = lvl[v] + 1; q.push_back(es[id].to); } }
        return lvl[t] >= 0;
    }
    ll dfs(int v, int t, ll f) {
        if (v == t || f == 0) return f;
        ll pushed = 0;
        for (int &i = it[v]; i < (int)g[v].size(); i++) {
            int id = g[v][i]; int w = es[id].to;
            if (es[id].cap <= 0 || lvl[w] != lvl[v] + 1) continue;
            ll d = dfs(w, t, min(f - pushed, es[id].cap));
            if (d > 0) { es[id].cap -= d; es[id ^ 1].cap += d; pushed += d; if (pushed == f) return pushed; }
        }
        return pushed;
    }
    ll flow(int s, int t) { ll r = 0; while (bfs(s, t)) { fill(it.begin(), it.end(), 0); r += dfs(s, t, LLONG_MAX / 4); } return r; }
};
int main() {
    int n, m, k;
    if (scanf("%d %d %d", &n, &m, &k) != 3) return 0;
    const int LG = 6; const ll INF = LLONG_MAX / 4;
    auto id = [&](int p, int q, int i, int j) { return ((p * LG + q) * 50 + i) * 50 + j; };
    int S = LG * LG * 2500, T = S + 1;
    // merge customers with identical rectangles
    map<array<int, 4>, ll> cust;
    vector<vector<ll>> a(n, vector<ll>(m));
    for (auto &r : a) for (auto &x : r) scanf("%lld", &x);
    for (int i = 0; i < k; i++) { int t, b, l, r; ll x; scanf("%d %d %d %d %lld", &t, &b, &l, &r, &x); cust[{t - 1, b - 1, l - 1, r - 1}] += x; }
    Dinic D(T + 1 + cust.size());
    for (int p = 0; p < LG; p++) for (int q = 0; q < LG; q++)
        for (int i = 0; i + (1 << p) <= n; i++) for (int j = 0; j + (1 << q) <= m; j++) {
            int v = id(p, q, i, j);
            if (p > 0) { D.add(v, id(p - 1, q, i, j), INF); D.add(v, id(p - 1, q, i + (1 << (p - 1)), j), INF); }
            else if (q > 0) { D.add(v, id(p, q - 1, i, j), INF); D.add(v, id(p, q - 1, i, j + (1 << (q - 1))), INF); }
            else if (a[i][j] > 0) D.add(v, T, a[i][j]);
        }
    int c = T + 1;
    for (auto &kv : cust) {
        if (kv.second > 0) {
            int t = kv.first[0], b = kv.first[1], l = kv.first[2], r = kv.first[3];
            int p = 31 - __builtin_clz(b - t + 1), q = 31 - __builtin_clz(r - l + 1);
            D.add(S, c, kv.second);
            int i2 = b - (1 << p) + 1, j2 = r - (1 << q) + 1;
            D.add(c, id(p, q, t, l), INF);
            if (i2 != t) D.add(c, id(p, q, i2, l), INF);
            if (j2 != l) D.add(c, id(p, q, t, j2), INF);
            if (i2 != t && j2 != l) D.add(c, id(p, q, i2, j2), INF);
        }
        c++;
    }
    printf("%lld\n", D.flow(S, T));
}
