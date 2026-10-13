#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// Feasible iff U >= N-1 and R >= M-1 (every lower row needs a U, every non-last column an R);
// with one row/column everything is forced.
// Construction: D's fill columns from the left (rows 0..N-2), whose bottom cells go R.
// The partial column q holds s D's and then an R at row s. In the remaining columns,
// row 0 is all R and every other row is R^a U^b L^c with b >= 1 (rows 1..s start at
// column q+1, rows below s at column q). Any split of the leftover R/U/L works.
int main() {
    int T;
    scanf("%d", &T);
    string out;
    for (int tc = 0; tc < T; tc++) {
        ll N, M, U, R, D, L;
        scanf("%lld %lld %lld %lld %lld %lld", &N, &M, &U, &R, &D, &L);
        if (tc) out += '\n';
        bool ok = (U >= N - 1 && R >= M - 1);
        if (N == 1 && R != M - 1) ok = false;
        if (M == 1 && U != N - 1) ok = false;
        if (!ok) { out += "impossible\n"; continue; }
        vector<string> g(N, string(M, '?'));
        if (N == 1) { for (int c = 0; c < M - 1; c++) g[0][c] = 'R'; }
        else if (M == 1) { for (int r = 1; r < N; r++) g[r][0] = 'U'; }
        else {
            ll q = D / (N - 1), s = D % (N - 1);
            for (int c = 0; c < q; c++) {
                for (int r = 0; r < N - 1; r++) g[r][c] = 'D';
                g[N - 1][c] = 'R';
            }
            ll ru = U - (N - 1), rr = R - (M - 1), rl = L; // leftovers
            for (int r = 0; r < s; r++) g[r][q] = 'D';
            if (s > 0) g[s][q] = 'R';
            for (int c = (s > 0 ? q + 1 : q); c < M - 1; c++) g[0][c] = 'R';
            for (int r = 1; r < N; r++) {
                int c0 = (r <= s) ? q + 1 : q;
                ll fre = M - c0 - 1;
                ll a = min(rr, fre); rr -= a; fre -= a;
                ll b = min(ru, fre); ru -= b; fre -= b;
                ll c = min(rl, fre); rl -= c; fre -= c;
                int p = c0;
                for (ll i = 0; i < a; i++) g[r][p++] = 'R';
                for (ll i = 0; i < b + 1; i++) g[r][p++] = 'U';
                for (ll i = 0; i < c; i++) g[r][p++] = 'L';
            }
        }
        g[0][M - 1] = '*';
        for (auto &row : g) { out += row; out += '\n'; }
    }
    fputs(out.c_str(), stdout);
}
