#include <bits/stdc++.h>
using namespace std;
// phi(m^2) = prod p^(2k-1) (p-1). Peel primes of a/b from the largest down:
// the (p-1) factor only disturbs smaller primes.
int e[10010];
void addf(int x, int s) {
    for (int p = 2; p * p <= x; p++)
        while (x % p == 0) { e[p] += s; x /= p; }
    if (x > 1) e[x] += s;
}
int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    addf(a, 1); addf(b, -1);
    unsigned long long m = 1, n = 1;
    for (int p = 10007; p >= 2; p--) {
        if (e[p] == 0) continue;
        int v = abs(e[p]);
        int big, small;            // exponents of p on the heavy side / light side
        if (v & 1) { big = (v + 1) / 2; small = 0; }
        else { big = v / 2 + 1; small = 1; }
        unsigned long long &hi = e[p] > 0 ? m : n, &lo = e[p] > 0 ? n : m;
        for (int i = 0; i < big; i++) hi *= p;
        for (int i = 0; i < small; i++) lo *= p;
        int sg = e[p] > 0 ? 1 : -1;
        e[p] = 0;
        if (small == 0) addf(p - 1, -sg);   // heavy side contributed an unmatched (p-1)
    }
    printf("%llu %llu\n", m, n);
}
