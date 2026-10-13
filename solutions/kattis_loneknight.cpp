#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifndef TT
#define TT 7
#endif
static const ll W = 1LL << 40;
struct Axis {
    vector<ll> b;            // blocked coords sorted
    vector<ll> gl, gw;       // gap left coordinate and true width
    vector<int> gc, gf;      // compressed start and compressed width
    int size;
    void build() {
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        int k = b.size();
        gl.resize(k + 1); gw.resize(k + 1); gc.resize(k + 1); gf.resize(k + 1);
        for (int i = 0; i <= k; i++) {
            if (i == 0) { gl[i] = b[0] - W; gw[i] = W; }
            else if (i == k) { gl[i] = b[k - 1] + 1; gw[i] = W; }
            else { gl[i] = b[i - 1] + 1; gw[i] = b[i] - b[i - 1] - 1; }
        }
        int pos = 2; // padding
        for (int i = 0; i <= k; i++) {
            ll w = gw[i];
            ll f = w;
            if (w > TT) f = w - 4 * ((w - TT + 3) / 4);
            gc[i] = pos; gf[i] = (int)f;
            pos += (int)f;
            if (i < k) pos++; // blocked line
        }
        size = pos + 2;
    }
    bool blocked(ll x) const { return binary_search(b.begin(), b.end(), x); }
    int blockedIdx(int i) const { return gc[i] + gf[i]; }
    int mp(ll x) const {
        int i = upper_bound(b.begin(), b.end(), x) - b.begin();
        ll d = x - gl[i];
        if (gw[i] > TT) d %= 4;
        return gc[i] + (int)d;
    }
};
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    Axis X, Y;
    for (int i = 0; i < n; i++) {
        ll x, y; scanf("%lld %lld", &x, &y);
        X.b.push_back(x); Y.b.push_back(y);
    }
    X.build(); Y.build();
    int SX = X.size, SY = Y.size;
    vector<unsigned short> lab((size_t)SX * SY, 0);
    const unsigned short BL = 0xFFFF;
    auto at = [&](int x, int y) -> unsigned short& { return lab[(size_t)y * SX + x]; };
    for (int y = 0; y < SY; y++) for (int x = 0; x < SX; x++)
        if (x < 2 || y < 2 || x >= SX - 2 || y >= SY - 2) at(x, y) = BL;
    for (size_t i = 0; i < X.b.size(); i++) { int c = X.blockedIdx(i); for (int y = 0; y < SY; y++) at(c, y) = BL; }
    for (size_t i = 0; i < Y.b.size(); i++) { int c = Y.blockedIdx(i); for (int x = 0; x < SX; x++) at(x, c) = BL; }
    const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1}, dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    ptrdiff_t off[8];
    for (int k = 0; k < 8; k++) off[k] = (ptrdiff_t)dy[k] * SX + dx[k];
    vector<array<ll, 4>> qs(q);
    for (auto& a : qs) scanf("%lld %lld %lld %lld", &a[0], &a[1], &a[2], &a[3]);
    unsigned short nextLab = 0;
    vector<size_t> cur, nxt;
    auto fill = [&](size_t s) {
        if (lab[s] != 0) return;
        ++nextLab;
        lab[s] = nextLab;
        cur.clear(); cur.push_back(s);
        while (!cur.empty()) {
            nxt.clear();
            for (size_t c : cur) for (int k = 0; k < 8; k++) {
                size_t t = c + off[k];
                if (lab[t] == 0) { lab[t] = nextLab; nxt.push_back(t); }
            }
            swap(cur, nxt);
        }
    };
    for (auto& a : qs) {
        size_t s = (size_t)Y.mp(a[1]) * SX + X.mp(a[0]);
        size_t t = (size_t)Y.mp(a[3]) * SX + X.mp(a[2]);
        fill(s); fill(t);
        int ans = lab[s] == lab[t];
        if (ans && s == t) {
            // same compressed cell: connected unless the start has no legal move at all
            bool any = false;
            for (int k = 0; k < 8; k++)
                if (!X.blocked(a[0] + dx[k]) && !Y.blocked(a[1] + dy[k])) any = true;
            if (!any) ans = 0;
        }
        printf("%d\n", ans);
    }
}
