#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
// E[T] = sum_{t>=0} P(not sorted after t pops); after t pops the survivors are a uniform
// (n-t)-subset. So we need cnt[k] = number of sorted k-subsets for every k.
// Automaton with state = largest colour kept so far; each balloon is a 3x3 upper
// triangular matrix of polynomials in x (x marks "kept"). Multiply all of them by
// divide and conquer + NTT. Diagonal entries are (1+x)^count in closed form.
const ll MOD = 998244353;
ll pw(ll b, ll e) { ll r = 1; b %= MOD; while (e) { if (e & 1) r = r * b % MOD; b = b * b % MOD; e >>= 1; } return r; }
typedef vector<unsigned> poly;
void ntt(vector<unsigned> &a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    static vector<unsigned> rt;
    for (int len = 2; len <= n; len <<= 1) {
        ll w = pw(3, (MOD - 1) / len);
        if (inv) w = pw(w, MOD - 2);
        int h = len / 2;
        rt.resize(h);
        rt[0] = 1;
        for (int i = 1; i < h; i++) rt[i] = (ull)rt[i - 1] * w % MOD;
        for (int i = 0; i < n; i += len)
            for (int j = 0; j < h; j++) {
                unsigned u = a[i + j], v = (ull)a[i + j + h] * rt[j] % MOD;
                unsigned s = u + v; if (s >= MOD) s -= MOD;
                unsigned d = u + MOD - v; if (d >= MOD) d -= MOD;
                a[i + j] = s; a[i + j + h] = d;
            }
    }
    if (inv) {
        ll ni = pw(n, MOD - 2);
        for (auto &x : a) x = (ull)x * ni % MOD;
    }
}
vector<ll> fact, inv;
ll C(int n, int k) { if (k < 0 || k > n) return 0; return fact[n] * inv[k] % MOD * inv[n - k] % MOD; }
poly binom(int c) { poly p(c + 1); for (int i = 0; i <= c; i++) p[i] = C(c, i); return p; }
bool isZero(const poly &p) { return p.empty(); }
struct Node { int cb, cy, cr; poly m01, m02, m12; };
string s;
// result = sum of products A_i * B_i, truncated to size `len`
poly sumprod(vector<pair<const poly *, const poly *>> terms, int len) {
    vector<pair<const poly *, const poly *>> t;
    for (auto &pr : terms) if (!pr.first->empty() && !pr.second->empty()) t.push_back(pr);
    if (t.empty()) return poly();
    size_t mx = 0, small = 1;
    for (auto &pr : t) { mx = max(mx, pr.first->size() + pr.second->size() - 1); if (min(pr.first->size(), pr.second->size()) > 32) small = 0; }
    poly res;
    if (small) {
        vector<ull> acc(mx, 0);
        for (auto &pr : t) {
            const poly &a = *pr.first, &b = *pr.second;
            const poly &x = a.size() < b.size() ? a : b, &y = a.size() < b.size() ? b : a;
            for (size_t i = 0; i < x.size(); i++) if (x[i]) {
                for (size_t j = 0; j < y.size(); j++) acc[i + j] = (acc[i + j] + (ull)x[i] * y[j]) % MOD;
            }
        }
        res.assign(acc.begin(), acc.end());
    } else {
        int sz = 1; while ((size_t)sz < mx) sz <<= 1;
        vector<unsigned> acc(sz, 0);
        map<const poly *, vector<unsigned>> cache;
        auto get = [&](const poly *p) -> vector<unsigned> & {
            auto it = cache.find(p);
            if (it != cache.end()) return it->second;
            vector<unsigned> v(p->begin(), p->end());
            v.resize(sz);
            ntt(v, false);
            return cache[p] = std::move(v);
        };
        for (auto &pr : t) {
            vector<unsigned> &fa = get(pr.first);
            vector<unsigned> &fb = get(pr.second);
            for (int i = 0; i < sz; i++) acc[i] = (acc[i] + (ull)fa[i] * fb[i]) % MOD;
        }
        ntt(acc, true);
        acc.resize(mx);
        res = std::move(acc);
    }
    if ((int)res.size() > len) res.resize(len);
    return res;
}
Node build(int l, int r) {
    Node nd;
    if (r - l == 1) {
        nd.cb = s[l] == 'B'; nd.cy = s[l] == 'Y'; nd.cr = s[l] == 'R';
        if (s[l] == 'Y') nd.m01 = {0, 1};
        if (s[l] == 'R') { nd.m02 = {0, 1}; nd.m12 = {0, 1}; }
        return nd;
    }
    int m = (l + r) / 2;
    Node A = build(l, m), B = build(m, r);
    nd.cb = A.cb + B.cb; nd.cy = A.cy + B.cy; nd.cr = A.cr + B.cr;
    poly a00 = binom(A.cb), a11 = binom(A.cy), b11 = binom(B.cy), b22 = binom(B.cr);
    int len = r - l + 1;
    nd.m01 = sumprod({{&a00, &B.m01}, {&A.m01, &b11}}, len);
    nd.m02 = sumprod({{&a00, &B.m02}, {&A.m01, &B.m12}, {&A.m02, &b22}}, len);
    nd.m12 = sumprod({{&a11, &B.m12}, {&A.m12, &b22}}, len);
    return nd;
}
int main() {
    cin >> s;
    int n = s.size();
    fact.assign(n + 2, 1); inv.assign(n + 2, 1);
    for (int i = 1; i <= n + 1; i++) fact[i] = fact[i - 1] * i % MOD;
    inv[n + 1] = pw(fact[n + 1], MOD - 2);
    for (int i = n + 1; i > 0; i--) inv[i - 1] = inv[i] * i % MOD;
    Node R = build(0, n);
    ll ans = 0;
    for (int k = 1; k <= n; k++) {
        ll cnt = C(R.cb, k);
        if (k < (int)R.m01.size()) cnt += R.m01[k];
        if (k < (int)R.m02.size()) cnt += R.m02[k];
        cnt %= MOD;
        ll ic = inv[n] * fact[k] % MOD * fact[n - k] % MOD;
        ans = (ans + 1 - cnt * ic % MOD + MOD) % MOD;
    }
    printf("%lld\n", ans);
}
