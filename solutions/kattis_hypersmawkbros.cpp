#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// Losing positions L_0=0<L_1<...; consecutive gaps are m+1 or m+2.
// In block k (positions L_k+y, 1<=y<=m) let U_k = {y : the only winning move is y (to L_k)}.
// gap_k = m+2 iff m odd and (m+1)/2 in U_k. Membership is evaluated lazily with memoisation.
static int m, h;
static vector<int> gap_;
static unordered_map<ll, char> memo;
static bool in(int k, int y) {
    if (k == 0) return y == m;
    ll key = (ll)k * (m + 2) + y;
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    bool r = true;
    int g = gap_[k - 1];
    if (g == m + 2 && y == h - 1) r = false;            // hit by the special position of the previous block
    if (r && ((y + g) % 2 == 0)) {
        int z = (y + g) / 2;
        if (z <= m && in(k - 1, z)) r = false;         // hit from previous block: L_{k-1}+z plays z
    }
    if (r && y % 2 == 0 && in(k, y / 2)) r = false;     // hit from inside the block
    memo[key] = r;
    return r;
}
int main() {
    int t;
    scanf("%d", &t);
    vector<int> N(t), M(t);
    vector<char> ans(t, 1);
    map<int, vector<int>> byM;
    for (int i = 0; i < t; i++) {
        scanf("%d %d", &N[i], &M[i]);
        if (N[i] <= M[i]) continue;
        if (M[i] % 2 == 0) { ans[i] = (N[i] % (M[i] + 1) != 0); continue; }
        byM[M[i]].push_back(i);
    }
    for (auto &pr : byM) {
        m = pr.first; h = (m + 1) / 2;
        int mx = 0;
        for (int i : pr.second) mx = max(mx, N[i]);
        gap_.clear(); memo.clear();
        vector<int> L;
        ll cur = 0; int k = 0;
        while (true) {
            int g = in(k, h) ? m + 2 : m + 1;
            gap_.push_back(g); cur += g; k++;
            if (cur > mx) break;
            L.push_back((int)cur);
        }
        for (int i : pr.second) ans[i] = !binary_search(L.begin(), L.end(), N[i]);
    }
    for (int i = 0; i < t; i++) puts(ans[i] ? "YES" : "NO");
}
