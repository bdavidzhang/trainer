#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
// a*b panels fit iff (a w)^2 + (b h)^2 <= (2r)^2.  Enumerate the dimension with
// fewer panels, but only in a window of O(sqrt(b0)) around the continuous optimum
// b0 = sqrt(2) r / h: farther away the area loss exceeds the rounding loss.
static ull isq(ull x) {
    ull s = (ull)sqrtl((long double)x);
    while (s * s > x) s--;
    while ((s + 1) * (s + 1) <= x) s++;
    return s;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        ll r, w, h;
        scanf("%lld %lld %lld", &r, &w, &h);
        if (h < w) swap(w, h);           // b (count along h) is the smaller count
        ll B = 2 * r / h;
        ull R4 = 4ULL * r * r;
        ll best = 0;
        if (B >= 1) {
            long double b0 = sqrtl(2.0L) * r / h;
            ll win = (ll)(2 * sqrtl(b0)) + 100;
            ll lo = max(1LL, (ll)b0 - win), hi = min(B, (ll)b0 + win);
            for (ll b = lo; b <= hi; b++) {
                ull bh = (ull)b * h;
                ull rem = R4 - bh * bh;
                ll a = (ll)(isq(rem) / (ull)w);
                best = max(best, a * b);
            }
        }
        printf("%lld\n", best);
    }
}
