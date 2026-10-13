#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    vector<double> x(n), y(n);
    for (int i = 0; i < n; i++) scanf("%lf %lf", &x[i], &y[i]);
    // edge i -> i+1+g is on the hull iff i and j chosen and the g vertices between are not
    vector<double> pr(n, 0.0);
    auto lc = [](int a, int b) { return lgamma(a + 1.0) - lgamma(b + 1.0) - lgamma(a - b + 1.0); };
    double den = lc(n, k);
    for (int g = 0; g <= n - 2; g++) {
        int rem = n - 2 - g;
        if (rem >= k - 2) pr[g] = exp(lc(rem, k - 2) - den);
    }
    double ans = 0;
    for (int i = 0; i < n; i++) {
        double sx = 0, sy = 0;
        int j = i + 1;
        for (int g = 0; g <= n - 2; g++, j++) {
            if (j >= n) j -= n;
            if (pr[g] == 0) break;
            sx += pr[g] * x[j]; sy += pr[g] * y[j];
        }
        ans += x[i] * sy - y[i] * sx;
    }
    printf("%.8f\n", fabs(ans) / 2);
}
