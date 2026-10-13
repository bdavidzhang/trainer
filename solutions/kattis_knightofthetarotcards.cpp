#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// Lattice of a card (a,b) is the Gaussian ideal (z, conj z) = d*(1+i)^e, d = gcd(a,b), e = [a/d,b/d both odd].
typedef pair<ll,int> St; // (d, e); d==0 means no card yet
static St combine(St A, St B) {
    if (A.first == 0) return B;
    if (B.first == 0) return A;
    int va = __builtin_ctzll(A.first), vb = __builtin_ctzll(B.first);
    ll g = std::gcd(A.first >> va, B.first >> vb);
    int t = min(2 * va + A.second, 2 * vb + B.second);
    return St(g << (t / 2), t & 1);
}
static bool mem(const St& s, ll x, ll y) {
    if (s.first == 0) return x == 0 && y == 0;
    if (x % s.first || y % s.first) return false;
    if (s.second) return (((x / s.first) + (y / s.first)) & 1) == 0;
    return true;
}
int main() {
    int n;
    scanf("%d", &n);
    vector<ll> r(n), c(n), p(n);
    vector<St> cs(n);
    for (int i = 0; i < n; i++) {
        ll a, b;
        scanf("%lld %lld %lld %lld %lld", &r[i], &c[i], &a, &b, &p[i]);
        ll d = std::gcd(a, b);
        cs[i] = St(d, ((a / d) & 1) && ((b / d) & 1));
    }
    ll sr = r[0], sc = c[0];
    for (int i = 0; i < n; i++) r[i] -= sr, c[i] -= sc;
    map<St, ll> dist;
    priority_queue<pair<ll, St>, vector<pair<ll, St>>, greater<pair<ll, St>>> pq;
    St s0(0, 0);
    dist[s0] = 0;
    pq.push({0, s0});
    while (!pq.empty()) {
        auto [dd, s] = pq.top(); pq.pop();
        if (dist[s] != dd) continue;
        if (mem(s, -sr, -sc)) { printf("%lld\n", dd); return 0; }
        for (int i = 0; i < n; i++) {
            if (!mem(s, r[i], c[i])) continue;
            St ns = combine(s, cs[i]);
            if (ns == s) continue;
            ll nd = dd + p[i];
            auto it = dist.find(ns);
            if (it == dist.end() || it->second > nd) { dist[ns] = nd; pq.push({nd, ns}); }
        }
    }
    puts("-1");
}
