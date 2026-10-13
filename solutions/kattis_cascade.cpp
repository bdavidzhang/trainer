#include <bits/stdc++.h>
using namespace std;
// Cascade centrality = expected spread of the linear-threshold model seeded at x:
// every node picks one uniformly random neighbour as its "parent"; node j counts iff
// following parents from j reaches x (the path product 1/deg is exactly that probability).
// Exact: enumerate simple paths from x while a step budget lasts.
// Fallback (exact counting is #P-hard): Monte Carlo over the parent picks, error << 0.1.
static int n, m, X;
static vector<int> adj[105];
static int deg_[105];
static bool vis[105];
static long long budget;
static double total;
static bool dfs(int v, double w) {
    for (int u : adj[v]) if (!vis[u]) {
        if (--budget < 0) return false;
        double nw = w / deg_[u];
        total += nw; vis[u] = true;
        bool ok = dfs(u, nw);
        vis[u] = false;
        if (!ok) return false;
    }
    return true;
}
int main() {
    auto t0 = chrono::steady_clock::now();
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) { int u, v; scanf("%d %d", &u, &v); adj[u].push_back(v); adj[v].push_back(u); }
    scanf("%d", &X);
    for (int i = 1; i <= n; i++) deg_[i] = adj[i].size();
    budget = 60000000LL; total = 0; vis[X] = true;
    if (dfs(X, 1.0)) { printf("%.1f\n", 1.0 + total); return 0; }
    // Monte Carlo on the component of x
    vector<int> comp, id(n + 1, -1);
    comp.push_back(X); id[X] = 0;
    for (size_t h = 0; h < comp.size(); h++) for (int u : adj[comp[h]]) if (id[u] < 0) { id[u] = comp.size(); comp.push_back(u); }
    int c = comp.size();
    vector<int> off(c + 1, 0), nb;
    for (int i = 0; i < c; i++) { for (int u : adj[comp[i]]) nb.push_back(id[u]); off[i + 1] = nb.size(); }
    vector<int> par(c), stk(c); vector<unsigned char> st(c);
    uint64_t s0 = 0x9E3779B97F4A7C15ULL, s1 = 0xD1B54A32D192ED03ULL;
    auto rnd = [&]() -> uint64_t { uint64_t a = s0, b = s1; s0 = b; a ^= a << 23; s1 = a ^ b ^ (a >> 17) ^ (b >> 26); return s1 + b; };
    long long samples = 0; double sum = 0;
    while (true) {
        if ((samples & 2047) == 0) {
            double el = chrono::duration<double>(chrono::steady_clock::now() - t0).count();
            if (el > 5.5) break;
        }
        for (int i = 1; i < c; i++) {
            uint32_t d = off[i + 1] - off[i];
            par[i] = nb[off[i] + (int)(((rnd() >> 32) * d) >> 32)];
            st[i] = 0;
        }
        st[0] = 1; int cnt = 1; // 1 = reaches x, 2 = does not, 3 = on current chain
        for (int i = 1; i < c; i++) if (!st[i]) {
            int top = 0, v = i;
            while (!st[v]) { st[v] = 3; stk[top++] = v; v = par[v]; }
            unsigned char r = (st[v] == 1) ? 1 : 2;
            if (r == 1) cnt += top;
            while (top) st[stk[--top]] = r;
        }
        sum += cnt; samples++;
    }
    printf("%.3f\n", sum / samples);
}
