#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef array<ull, 5> Poly;
static Poly mul(const Poly &a, const Poly &b) {
    Poly r{}; for (int i = 0; i < 5; i++) if (a[i]) for (int j = 0; i + j < 5; j++) r[i + j] += a[i] * b[j];
    return r;
}
const int LG = 17;
int n, m, q;
vector<int> out_[100005], in_[100005];
int up[LG][100005], depD[100005], tin[100005], tout[100005];
int sid[100005], froot[100005], nz[100005], cls[100005], idx[100005];
ull H[100005], B[100005];
static int lca(int a, int b) {
    if (depD[a] < depD[b]) swap(a, b);
    int d = depD[a] - depD[b];
    for (int j = 0; j < LG; j++) if (d >> j & 1) a = up[j][a];
    if (a == b) return a;
    for (int j = LG - 1; j >= 0; j--) if (up[j][a] != up[j][b]) { a = up[j][a]; b = up[j][b]; }
    return up[0][a];
}
int main() {
    if (scanf("%d %d %d", &n, &m, &q) != 3) return 0;
    for (int i = 0; i < m; i++) { int x, y; scanf("%d %d", &x, &y); out_[x].push_back(y); in_[y].push_back(x); }
    vector<int> topo; topo.reserve(n);
    {
        vector<int> deg(n + 1);
        for (int v = 1; v <= n; v++) { deg[v] = in_[v].size(); if (!deg[v]) topo.push_back(v); }
        for (size_t i = 0; i < topo.size(); i++) for (int w : out_[topo[i]]) if (--deg[w] == 0) topo.push_back(w);
    }
    vector<int> spec;
    for (int v = 1; v <= n; v++) { sid[v] = -1; if (v != 1 && in_[v].size() >= 2) { sid[v] = spec.size(); spec.push_back(v); } }
    // dominator tree of a DAG: idom = LCA of predecessors' positions in the tree built so far
    vector<vector<int>> ch(n + 1);
    for (int v : topo) {
        int d = 0;
        if (v != 1) { d = in_[v][0]; for (size_t i = 1; i < in_[v].size(); i++) d = lca(d, in_[v][i]); }
        up[0][v] = d; depD[v] = depD[d] + 1;
        for (int j = 1; j < LG; j++) up[j][v] = up[j - 1][up[j - 1][v]];
        if (d) ch[d].push_back(v);
        froot[v] = (v == 1 || sid[v] >= 0) ? v : froot[in_[v][0]];
    }
    { // euler tour of D
        int timer = 0; vector<pair<int, int>> st; st.push_back({1, 0}); tin[1] = timer++;
        while (!st.empty()) {
            int v = st.back().first; int &i = st.back().second;
            if (i < (int)ch[v].size()) { int w = ch[v][i++]; tin[w] = timer++; st.push_back({w, 0}); }
            else { tout[v] = timer - 1; st.pop_back(); }
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        int v = topo[i]; ull h = 0;
        for (int w : out_[v]) { h |= H[w]; if (sid[w] >= 0) h |= 1ULL << sid[w]; }
        H[v] = h;
        ull b = 0;
        for (ull t = h; t; t &= t - 1) { int s = spec[__builtin_ctzll(t)]; if (!(tin[v] <= tin[s] && tin[s] <= tout[v])) b |= 1ULL << sid[s]; }
        B[v] = b; // specials reachable from v but not dominated by v
    }
    // classes: connected same-B components among nodes with B != 0 (along dominator tree)
    vector<ull> cmask; vector<int> pc, pidx;
    for (int v : topo) {
        int p = up[0][v]; int pn = p ? nz[p] : 0;
        if (B[v] == 0) { nz[v] = pn; continue; }
        nz[v] = v;
        if (pn && B[pn] == B[v]) { cls[v] = cls[pn]; idx[v] = idx[pn] + 1; }
        else { cls[v] = cmask.size(); idx[v] = 1; cmask.push_back(B[v]); pc.push_back(pn ? cls[pn] : -1); pidx.push_back(pn ? idx[pn] : 0); }
    }
    int C = cmask.size();
    vector<char> bad(C); vector<int> base(C);
    auto Pf = [&](int v) -> long long { // number of good nodes among dominator-ancestors-or-self of v
        if (!v) return 0;
        int u = nz[v]; long long bc = 0;
        if (u) { int c = cls[u]; bc = base[c] + (bad[c] ? idx[u] : 0); }
        return depD[v] - bc;
    };
    vector<char> inQ(n + 1, 0);
    vector<Poly> prod(n + 1);
    vector<int> nodes, stk, par;
    string outs;
    while (q--) {
        int k, a; scanf("%d %d", &k, &a);
        nodes.resize(a); ull M = 0;
        for (int i = 0; i < a; i++) { scanf("%d", &nodes[i]); inQ[nodes[i]] = 1; int r = froot[nodes[i]]; if (sid[r] >= 0) M |= 1ULL << sid[r]; }
        for (int c = 0; c < C; c++) {
            bad[c] = (cmask[c] & M) != 0;
            base[c] = pc[c] < 0 ? 0 : base[pc[c]] + (bad[pc[c]] ? pidx[c] : 0);
        }
        auto cmp = [&](int x, int y) { return tin[x] < tin[y]; };
        sort(nodes.begin(), nodes.end(), cmp);
        for (int i = 0; i + 1 < a; i++) nodes.push_back(lca(nodes[i], nodes[i + 1]));
        sort(nodes.begin(), nodes.end(), cmp);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        int sz = nodes.size();
        par.assign(sz, -1); stk.clear();
        for (int i = 0; i < sz; i++) {
            int v = nodes[i];
            while (!stk.empty() && !(tin[nodes[stk.back()]] <= tin[v] && tin[v] <= tout[nodes[stk.back()]])) stk.pop_back();
            if (!stk.empty()) par[i] = stk.back();
            stk.push_back(i);
            prod[v] = Poly{1, 0, 0, 0, 0};
        }
        ull ans = 0;
        for (int i = sz - 1; i >= 0; i--) {
            int v = nodes[i];
            long long pv = Pf(v), pp = Pf(up[0][v]);
            Poly f = inQ[v] ? Poly{} : prod[v];
            if (pv - pp == 1) f[1] += 1;
            if (par[i] < 0) { f[1] += pp; ans = f[k]; }
            else { int u = nodes[par[i]]; f[1] += pp - Pf(u); prod[u] = mul(prod[u], f); }
        }
        for (int v : nodes) inQ[v] = 0;
        outs += to_string(ans); outs += '\n';
    }
    fputs(outs.c_str(), stdout);
    if (getenv("SKI_DEBUG")) fprintf(stderr, "classes=%d\n", C);
}
