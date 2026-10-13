#include <bits/stdc++.h>
using namespace std;
int main() {
    int b, p;
    scanf("%d %d", &b, &p);
    vector<int> x(p);
    for (int i = p - 1; i >= 0; i--) scanf("%d", &x[i]);
    int S = 0;
    for (int v : x) S += v;
    const int INF = INT_MAX / 2;
    vector<int> d0(S + 1, INF), d1(S + 1, INF), n0(S + 1), n1(S + 1);
    d0[0] = 0;
    int hi = 0; // max alice count in use
    for (int i = 0; i < p; i++) {
        int nh = min(S, hi + b);
        fill(n0.begin(), n0.begin() + nh + 1, INF);
        fill(n1.begin(), n1.begin() + nh + 1, INF);
        for (int c = 0; c < 2; c++) {
            vector<int>& d = c ? d1 : d0;
            int e = x[i] + c;
            if (e == 0) { for (int a = 0; a <= hi; a++) n0[a] = min(n0[a], d[a]); }
            else if (e == b) { for (int a = 0; a <= hi; a++) n1[a] = min(n1[a], d[a]); }
            else {
                for (int a = 0; a <= hi; a++) {
                    if (d[a] >= INF) continue;
                    if (a + e <= S) n0[a + e] = min(n0[a + e], d[a]);
                    n1[a] = min(n1[a], d[a] + b - e);
                }
            }
        }
        hi = nh;
        swap(d0, n0); swap(d1, n1);
    }
    int ans = INF;
    for (int a = 0; a <= hi; a++) {
        ans = min(ans, max(a, d0[a]));
        ans = min(ans, max(a, d1[a]));
    }
    printf("%d\n", ans);
}
