#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull MOD = 998244353;
static ull pw(ull b, ull e) { ull r = 1; b %= MOD; while (e) { if (e & 1) r = r * b % MOD; b = b * b % MOD; e >>= 1; } return r; }
static void ntt(vector<unsigned> &a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) { int bit = n >> 1; for (; j & bit; bit >>= 1) j ^= bit; j ^= bit; if (i < j) swap(a[i], a[j]); }
    for (int len = 2; len <= n; len <<= 1) {
        ull w = pw(3, (MOD - 1) / len); if (inv) w = pw(w, MOD - 2);
        int h = len / 2; vector<unsigned> ws(h); ws[0] = 1;
        for (int i = 1; i < h; i++) ws[i] = (ull)ws[i - 1] * w % MOD;
        for (int i = 0; i < n; i += len) for (int j = 0; j < h; j++) {
            unsigned u = a[i + j]; unsigned v = (ull)a[i + j + h] * ws[j] % MOD;
            unsigned x = u + v; if (x >= MOD) x -= MOD; a[i + j] = x;
            a[i + j + h] = u >= v ? u - v : u + (unsigned)MOD - v;
        }
    }
    if (inv) { ull ni = pw(n, MOD - 2); for (auto &x : a) x = x * ni % MOD; }
}
int main() {
    static char buf[1000005];
    if (scanf("%1000001s", buf) != 1) return 0;
    int n = strlen(buf);
    int sz = 1; while (sz < 2 * n) sz <<= 1;
    vector<unsigned> A(sz, 0), B(sz, 0);
    for (int i = 0; i < n; i++) { if (buf[i] == 'A') A[i] = 1; else B[n - 1 - i] = 1; }
    ntt(A, false); ntt(B, false);
    for (int i = 0; i < sz; i++) A[i] = (ull)A[i] * B[i] % MOD;
    ntt(A, true);
    string out;
    for (int k = 1; k < n; k++) { out += to_string(A[n - 1 + k]); out += '\n'; }
    fputs(out.c_str(), stdout);
}
