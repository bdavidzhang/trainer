#include <bits/stdc++.h>
using namespace std;
int main() {
    int score[2] = {0, 0};
    for (int f = 0; f < 10; f++) {
        vector<long long> d[2];
        for (int t = 0; t < 2; t++) {
            int n; scanf("%d", &n);
            for (int i = 0; i < n; i++) { long long x, y; scanf("%lld %lld", &x, &y); d[t].push_back((x - 144) * (x - 144) + (y - 84) * (y - 84)); }
        }
        for (int t = 0; t < 2; t++) {
            long long opp = LLONG_MAX; for (long long v : d[1 - t]) opp = min(opp, v);
            for (long long v : d[t]) if (v < opp) score[t]++;
        }
    }
    printf("%d %d\n", score[0], score[1]);
}
