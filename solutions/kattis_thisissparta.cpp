#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 LL;
// One round on sorted a: b1 = a1, b_i = a_i - b_{i-1}; prefix sums obey
// P_k(b) = (P_k(a) + b_k)/2 <= P_k(a) - P_{k-1}(a)/2. Hence keeping d+1 non-zero
// gladiators alive for T rounds needs total >= T^d / (2^d d!): after ~120 rounds at most
// ~57 are non-zero, after ~6e6 rounds at most 3. So simulate naively while >= 4 are
// non-zero, and fast-forward the 3- and 2-element cases (Euclid-like closed forms).
static void radixSort(vector<ull> &a, vector<ull> &tmp) {
    size_t n = a.size();
    ull mx = 0;
    for (ull x : a) mx |= x;
    tmp.resize(n);
    static unsigned cnt[1 << 11];
    for (int sh = 0; sh < 64 && (mx >> sh); sh += 11) {
        memset(cnt, 0, sizeof cnt);
        for (size_t i = 0; i < n; i++) cnt[(a[i] >> sh) & 2047]++;
        unsigned s = 0;
        for (int i = 0; i < 2048; i++) { unsigned c = cnt[i]; cnt[i] = s; s += c; }
        for (size_t i = 0; i < n; i++) tmp[cnt[(a[i] >> sh) & 2047]++] = a[i];
        a.swap(tmp);
    }
}
static void sortDrop(vector<ull> &a, vector<ull> &tmp) {
    size_t n = a.size();
    if (n <= 48) {
        for (size_t i = 1; i < n; i++) {
            ull x = a[i]; size_t j = i;
            while (j > 0 && a[j - 1] > x) { a[j] = a[j - 1]; j--; }
            a[j] = x;
        }
    } else if (n <= 4096) sort(a.begin(), a.end());
    else radixSort(a, tmp);
    size_t z = 0;
    while (z < n && a[z] == 0) z++;
    if (z) a.erase(a.begin(), a.begin() + z);
}
int main() {
    int n; ull K;
    scanf("%d %llu", &n, &K);
    vector<ull> a(n), tmp;
    for (auto &x : a) scanf("%llu", &x);
    sortDrop(a, tmp);
    ull rem = K - 1; // rounds followed by a re-sort
    while (rem > 0 && a.size() >= 2) {
        size_t m = a.size();
        if (m >= 4) {
            for (size_t i = 1; i < m; i++) a[i] -= a[i - 1];
            rem--;
            sortDrop(a, tmp);
        } else if (m == 3) {
            ull x = a[0], y = a[1], z = a[2];
            // after s rounds with unchanged order: (x, y - s x, z - s y + s(s+1)/2 x)
            ull s1 = y / x;                 // first s with y - s x < x
            ull lim = min(rem, s1);
            auto g = [&](ull s) -> LL {     // z_s - y_s
                return (LL)z - (LL)s * y + (LL)s * (s + 1) / 2 * x - (LL)y + (LL)s * x;
            };
            ull t = lim;
            ull hiS = min(lim, s1 - 1);     // g is non-increasing on [0, s1-1]
            if (hiS >= 1 && g(hiS) < 0) {
                ull lo = 1, hi = hiS;
                while (lo < hi) { ull mid = lo + (hi - lo) / 2; if (g(mid) < 0) hi = mid; else lo = mid + 1; }
                t = lo;
            }
            LL nz = (LL)z - (LL)t * y + (LL)t * (t + 1) / 2 * x;
            a[1] = y - t * x;
            a[2] = (ull)nz;
            rem -= t;
            sortDrop(a, tmp);
        } else {
            ull x = a[0], y = a[1];
            ull t = min(rem, y / x);
            a[1] = y - t * x;
            rem -= t;
            sortDrop(a, tmp);
        }
    }
    // final round, printed in line order
    size_t m = a.size();
    for (size_t i = 1; i < m; i++) a[i] -= a[i - 1];
    string out;
    for (size_t i = 0; i < (size_t)n - m; i++) out += "0 ";
    for (size_t i = 0; i < m; i++) { out += to_string(a[i]); out += ' '; }
    out.back() = '\n';
    fputs(out.c_str(), stdout);
}
