#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return 0;
    static char s[100005];
    scanf("%100001s", s);
    vector<int> c(n);
    long long sumneg = 0;
    for (int i = 0; i < n; i++) { scanf("%d", &c[i]); if (c[i] < 0) sumneg += c[i]; }
    if (n % 2 == 1) { printf("%lld\n", sumneg); return 0; }
    if (k >= n / 2 + 1) { puts("?"); return 0; }
    // split m: prefix [0,m) wants ')', suffix wants '('. bad = wrong char after taking all negative flips.
    // need (#bad) <= n/2 - k - 1 + (m odd); fixing a bad position costs |c|.
    vector<int> cntv(1001, 0);
    int badcnt = 0;
    auto sufBad = [&](int i) { return (s[i] == ')') != (c[i] < 0); };
    for (int i = 0; i < n; i++) if (sufBad(i)) { cntv[abs(c[i])]++; badcnt++; }
    long long best = LLONG_MAX;
    for (int m = 0; m <= n; m++) {
        if (m > 0) {
            int i = m - 1; // toggles from suffix to prefix
            if (sufBad(i)) { cntv[abs(c[i])]--; badcnt--; } else { cntv[abs(c[i])]++; badcnt++; }
        }
        int L = n / 2 - k - 1 + (m & 1);
        if (L < 0) continue;
        int D = badcnt - L;
        long long extra = 0;
        for (int v = 0; v <= 1000 && D > 0; v++) {
            int t = min(D, cntv[v]);
            extra += (long long)t * v; D -= t;
        }
        best = min(best, extra);
    }
    if (best == LLONG_MAX) { puts("?"); return 0; }
    printf("%lld\n", sumneg + best);
}
