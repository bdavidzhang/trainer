#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// The graph is 2-connected series-parallel. Reduce: parallel edges (u,v) with best
// u-v path weights p,q give a cycle candidate p+q and merge to max(p,q); a vertex with
// two distinct neighbours is spliced out (series, weights add).
int main() {
    int V, E;
    scanf("%d %d", &V, &E);
    vector<unordered_map<int, ll>> adj(V + 1);
    ll best = LLONG_MIN;
    auto addEdge = [&](int a, int b, ll w) {
        auto it = adj[a].find(b);
        if (it == adj[a].end()) { adj[a][b] = w; adj[b][a] = w; }
        else {
            best = max(best, it->second + w);
            if (w > it->second) { it->second = w; adj[b][a] = w; }
        }
    };
    for (int i = 0; i < E; i++) {
        int a, b; ll s;
        scanf("%d %d %lld", &a, &b, &s);
        addEdge(a, b, s);
    }
    vector<int> st;
    vector<char> dead(V + 1, 0);
    for (int v = 1; v <= V; v++) if (adj[v].size() == 2) st.push_back(v);
    while (!st.empty()) {
        int v = st.back(); st.pop_back();
        if (dead[v] || adj[v].size() != 2) continue;
        auto it = adj[v].begin();
        int a = it->first; ll wa = it->second; ++it;
        int b = it->first; ll wb = it->second;
        dead[v] = 1;
        adj[v].clear();
        adj[a].erase(v); adj[b].erase(v);
        addEdge(a, b, wa + wb);
        if (adj[a].size() == 2) st.push_back(a);
        if (adj[b].size() == 2) st.push_back(b);
    }
    printf("%lld\n", best);
}
