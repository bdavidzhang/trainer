#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// Walk the boundary through unit cells (i,j). Crossing x=k changes i by +-1 and the
// point's value is j; crossing y=k changes j by +-1 and the value is i. So the signed
// value equals the change of i*j, which telescopes to 0 around the closed boundary:
// the crossings in the increasing direction sum to exactly half. Always solvable.
const ll S = 1000000;
static ll rd() {
    char buf[64];
    scanf("%63s", buf);
    bool neg = buf[0] == '-';
    char *p = buf + (neg ? 1 : 0);
    ll ip = 0, fp = 0;
    while (*p && *p != '.') ip = ip * 10 + (*p++ - '0');
    int d = 0;
    if (*p == '.') { p++; while (*p && d < 6) { fp = fp * 10 + (*p++ - '0'); d++; } }
    while (d < 6) { fp *= 10; d++; }
    ll v = ip * S + fp;
    return neg ? -v : v;
}
static ll fdiv(ll a, ll b) { // b > 0
    ll q = a / b, r = a % b;
    if (r < 0) q--;
    return q;
}
int main() {
    int n;
    scanf("%d", &n);
    vector<ll> x(n), y(n);
    for (int i = 0; i < n; i++) { x[i] = rd(); y[i] = rd(); }
    vector<int> out;
    ll total = 0;
    bool dbg = getenv("PP_DEBUG") != nullptr;
    for (int i = 0; i < n; i++) {
        ll x1 = x[i], y1 = y[i], x2 = x[(i + 1) % n], y2 = y[(i + 1) % n];
        for (int rep = 0; rep < 2; rep++) {
            // lines (first coord) = k crossed by segment; value floor(second coord)
            ll lo = min(x1, x2), hi = max(x1, x2);
            ll dx = x2 - x1, dy = y2 - y1;
            for (ll k = fdiv(lo, S) + 1; k <= fdiv(hi, S); k++) {
                ll K = k * S;
                // y = y1 + dy*(K-x1)/dx
                ll num = y1 * dx + dy * (K - x1), den = dx * S;
                if (den < 0) { num = -num; den = -den; }
                ll v = fdiv(num, den);
                total += v;
                if (dx > 0) out.push_back((int)v);
            }
            swap(x1, y1); swap(x2, y2);
        }
    }
    if (dbg) {
        ll s = 0;
        for (int v : out) s += v;
        fprintf(stderr, "points_total=%lld chosen=%lld ok=%d\n", total, s, (int)(2 * s == total));
    }
    string res = to_string(out.size()) + "\n";
    for (int v : out) { res += to_string(v); res += '\n'; }
    fputs(res.c_str(), stdout);
}
