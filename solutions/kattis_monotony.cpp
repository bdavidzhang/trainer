#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int r, c, a[20][20];
unsigned P[20][20];
int main() {
    scanf("%d %d", &r, &c);
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) scanf("%d", &a[i][j]);
    for (int i = 0; i < r; i++) for (int k = 0; k < r; k++) {
        unsigned m = 0;
        for (int j = 0; j < c; j++) if (a[i][j] < a[k][j]) m |= 1u << j;
        P[i][k] = m;
    }
    static unsigned lt[20][20];
    for (int j = 0; j < c; j++) for (int k = 0; k < c; k++) {
        unsigned m = 0;
        for (int i = 0; i < r; i++) if (a[i][j] < a[i][k]) m |= 1u << i;
        lt[j][k] = m;
    }
    unsigned full = (r == 32 ? ~0u : (1u << r) - 1);
    vector<unsigned> inc(1u << c), dec(1u << c);
    ull total = 0;
    int v[20]; unsigned pm[20][20]; ull f[20][20];
    for (unsigned S = 1; S < (1u << c); S++) {
        unsigned rest = S & (S - 1);
        if (!rest) inc[S] = dec[S] = full;
        else {
            int lo = __builtin_ctz(S), nx = __builtin_ctz(rest);
            inc[S] = inc[rest] & lt[lo][nx];
            dec[S] = dec[rest] & lt[nx][lo];
        }
        unsigned ok = inc[S] | dec[S];
        int m = 0;
        while (ok) { v[m++] = __builtin_ctz(ok); ok &= ok - 1; }
        total += m;
        for (int b = 0; b < m; b++) {
            for (int x = 0; x < b; x++) {
                unsigned pat = P[v[x]][v[b]] & S;
                pm[x][b] = pat;
                ull cnt = 1;
                for (int y = 0; y < x; y++) if (pm[y][x] == pat) cnt += f[y][x];
                f[x][b] = cnt;
                total += cnt;
            }
        }
    }
    printf("%llu\n", total);
}
