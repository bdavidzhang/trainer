#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
vector<array<ll, 3>> ed; // reversed: from v to u
const ll NEG = LLONG_MIN / 4, POS = LLONG_MAX / 4;
bool feasible(ll X) {
    // walk reversed edges from n; cumulative cost must never exceed X; can we reach 1?
    vector<ll> d(n + 1, POS);
    d[n] = 0;
    for (int it = 0; it < n; it++) {
        bool ch = false;
        for (auto& e : ed) {
            ll a = d[e[0]];
            if (a == POS) continue;
            ll c = a == NEG ? NEG : a + e[2];
            if (c <= X && c < d[e[1]]) { d[e[1]] = c; ch = true; }
        }
        if (!ch) break;
        if (d[1] != POS) return true;
    }
    if (d[1] != POS) return true;
    // anything still relaxable sits behind a feasible negative cycle
    bool any = false;
    for (auto& e : ed) {
        ll a = d[e[0]];
        if (a == POS) continue;
        ll c = a + e[2];
        if (c <= X && c < d[e[1]]) { d[e[1]] = NEG; any = true; }
    }
    if (!any) return false;
    for (int it = 0; it < n; it++) {
        bool ch = false;
        for (auto& e : ed) if (d[e[0]] == NEG && d[e[1]] != NEG) { d[e[1]] = NEG; ch = true; }
        if (!ch) break;
    }
    return d[1] == NEG;
}
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        ll u, v, s; scanf("%lld %lld %lld", &u, &v, &s);
        ed.push_back({v, u, s});
    }
    if (n == 1) { puts("0"); return 0; }
    ll lo = 0, hi = 2100LL * 1000000000LL;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (feasible(mid)) hi = mid; else lo = mid + 1;
    }
    printf("%lld\n", lo);
}
