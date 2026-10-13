#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    int n;
    scanf("%d", &n);
    vector<ll> x(n), y(n);
    for (int i = 0; i < n; i++) scanf("%lld %lld", &x[i], &y[i]);
    auto d2 = [&](int a, int b) { ll dx = x[a] - x[b], dy = y[a] - y[b]; return dx * dx + dy * dy; };
    int s = 0;
    for (int i = 1; i < n; i++) if (d2(0, i) > d2(0, s)) s = i; // farthest from any point is an endpoint
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    vector<ll> ds(n);
    for (int i = 0; i < n; i++) ds[i] = d2(s, i);
    sort(ord.begin(), ord.end(), [&](int a, int b) { return ds[a] < ds[b]; });
    long double tot = 0;
    for (int i = 0; i + 1 < n; i++) tot += sqrtl((long double)d2(ord[i], ord[i + 1]));
    printf("%.9Lf\n", tot);
}
