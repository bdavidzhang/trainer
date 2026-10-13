#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int main() {
    int n, w, h;
    if (scanf("%d %d %d", &n, &w, &h) != 3) return 0;
    n = min(n, w * h);
    vector<long long> dp(n + 1, 0), pre(n + 2), nd(n + 1);
    dp[0] = 1;
    for (int c = 0; c < w; c++) {
        pre[0] = 0;
        for (int j = 0; j <= n; j++) pre[j + 1] = (pre[j] + dp[j]) % MOD;
        for (int j = 0; j <= n; j++) { int lo = max(0, j - h); nd[j] = (pre[j + 1] - pre[lo] + MOD) % MOD; }
        dp = nd;
    }
    long long ans = 0;
    for (int j = 0; j <= n; j++) ans = (ans + dp[j]) % MOD;
    long long plains = min(h, n / w) + 1;
    ans = ((ans - plains) % MOD + MOD) % MOD;
    printf("%lld\n", ans);
}
