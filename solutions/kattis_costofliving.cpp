#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
int main() {
    int y, c, q;
    scanf("%d %d %d", &y, &c, &q);
    // unknowns: P_a (log price in year 1), M_a (log modifier), I_x (prefix log inflation, x=1..y-1 for year x+1)
    int V = 2 * c + (y - 1);
    vector<vector<ld>> A;
    const ld EPS = 1e-9L;
    for (int x = 0; x + 1 < y; x++) {
        double r; scanf("%lf", &r);
        if (r > 0) {
            vector<ld> row(V + 1, 0);
            row[2 * c + x] = 1;
            if (x > 0) row[2 * c + x - 1] = -1;
            row[V] = logl((ld)r);
            A.push_back(row);
        }
    }
    for (int x = 0; x < y; x++) for (int a = 0; a < c; a++) {
        double p; scanf("%lf", &p);
        if (p > 0) {
            vector<ld> row(V + 1, 0);
            row[a] = 1; row[c + a] = x;
            if (x > 0) row[2 * c + x - 1] = 1;
            row[V] = logl((ld)p);
            A.push_back(row);
        }
    }
    int m = A.size(), rk = 0;
    vector<int> pivRow(V, -1);
    for (int col = 0; col < V && rk < m; col++) {
        int best = -1; ld bv = EPS;
        for (int i = rk; i < m; i++) if (fabsl(A[i][col]) > bv) bv = fabsl(A[i][col]), best = i;
        if (best < 0) continue;
        swap(A[rk], A[best]);
        ld inv = 1 / A[rk][col];
        for (int j = col; j <= V; j++) A[rk][j] *= inv;
        for (int i = 0; i < m; i++) if (i != rk && fabsl(A[i][col]) > 0) {
            ld f = A[i][col];
            if (f == 0) continue;
            for (int j = col; j <= V; j++) A[i][j] -= f * A[rk][j];
            A[i][col] = 0;
        }
        pivRow[col] = rk++;
    }
    while (q--) {
        int a, b; scanf("%d %d", &a, &b); a--; b--;
        vector<ld> v(V, 0);
        v[a] = 1; v[c + a] = b;
        if (b > 0) v[2 * c + b - 1] = 1;
        ld val = 0; bool ok = true;
        for (int col = 0; col < V; col++) {
            if (fabsl(v[col]) < EPS) continue;
            if (pivRow[col] < 0) { ok = false; break; }
            ld f = v[col];
            const vector<ld>& row = A[pivRow[col]];
            for (int j = col; j < V; j++) v[j] -= f * row[j];
            val += f * row[V];
        }
        if (ok) printf("%.10f\n", (double)expl(val));
        else puts("-1.0");
    }
}
