#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct P3 { ll x, y, z; };
static P3 sub(P3 a, P3 b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
static P3 cross(P3 a, P3 b) { return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x}; }
static ll dot(P3 a, P3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
int n; vector<P3> p;
struct F { int a, b, c; };
static ll side(const F &f, int i) { return dot(cross(sub(p[f.b], p[f.a]), sub(p[f.c], p[f.a])), sub(p[i], p[f.a])); }
typedef pair<double, double> pd;
static double d2(pd a, pd b) { return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second); }
static void circ3(pd a, pd b, pd c, pd &o, double &r2) {
    double bx = b.first - a.first, by = b.second - a.second, cx = c.first - a.first, cy = c.second - a.second;
    double d = 2 * (bx * cy - by * cx);
    double ux = (cy * (bx * bx + by * by) - by * (cx * cx + cy * cy)) / d;
    double uy = (bx * (cx * cx + cy * cy) - cx * (bx * bx + by * by)) / d;
    o = {a.first + ux, a.second + uy}; r2 = ux * ux + uy * uy;
}
static double mec(vector<pd> &q) { // returns r^2
    int m = q.size(); pd o = q[0]; double r2 = 0; const double EPS = 1 + 1e-12;
    for (int i = 1; i < m; i++) if (d2(q[i], o) > r2 * EPS + 1e-12) {
        o = q[i]; r2 = 0;
        for (int j = 0; j < i; j++) if (d2(q[j], o) > r2 * EPS + 1e-12) {
            o = {(q[i].first + q[j].first) / 2, (q[i].second + q[j].second) / 2}; r2 = d2(q[i], o);
            for (int k = 0; k < j; k++) if (d2(q[k], o) > r2 * EPS + 1e-12) circ3(q[i], q[j], q[k], o, r2);
        }
    }
    return r2;
}
int main() {
    if (scanf("%d", &n) != 1) return 0;
    p.resize(n);
    for (auto &q : p) scanf("%lld %lld %lld", &q.x, &q.y, &q.z);
    mt19937 rng(12345);
    shuffle(p.begin(), p.end(), rng);
    // incremental hull; no four points coplanar, so no degeneracies
    vector<F> fs;
    auto addF = [&](int a, int b, int c, int inside) { F f{a, b, c}; if (side(f, inside) > 0) swap(f.b, f.c); fs.push_back(f); };
    addF(0, 1, 2, 3); addF(0, 1, 3, 2); addF(0, 2, 3, 1); addF(1, 2, 3, 0);
    vector<vector<int>> mark(n, vector<int>(n, -1)); // mark[a][b]=i : directed edge a->b belongs to a face visible from point i
    for (int i = 4; i < n; i++) {
        vector<F> keep, vis;
        for (auto &f : fs) { if (side(f, i) > 0) vis.push_back(f); else keep.push_back(f); }
        if (vis.empty()) continue;
        for (auto &f : vis) { mark[f.a][f.b] = i; mark[f.b][f.c] = i; mark[f.c][f.a] = i; }
        for (auto &f : vis) {
            int e[3][2] = {{f.a, f.b}, {f.b, f.c}, {f.c, f.a}};
            for (auto &ed : e) if (mark[ed[1]][ed[0]] != i) keep.push_back({ed[0], ed[1], i}); // horizon edge keeps orientation
        }
        fs.swap(keep);
    }
    double best = 1e300;
    vector<pd> q(n);
    for (auto &f : fs) {
        P3 nr = cross(sub(p[f.b], p[f.a]), sub(p[f.c], p[f.a]));
        double nl = sqrt((double)dot(nr, nr));
        double nx = nr.x / nl, ny = nr.y / nl, nz = nr.z / nl;
        // orthonormal basis of the plane
        double ax, ay, az;
        if (fabs(nx) <= fabs(ny) && fabs(nx) <= fabs(nz)) { ax = 1; ay = 0; az = 0; }
        else if (fabs(ny) <= fabs(nz)) { ax = 0; ay = 1; az = 0; }
        else { ax = 0; ay = 0; az = 1; }
        double ux = ny * az - nz * ay, uy = nz * ax - nx * az, uz = nx * ay - ny * ax;
        double ul = sqrt(ux * ux + uy * uy + uz * uz); ux /= ul; uy /= ul; uz /= ul;
        double vx = ny * uz - nz * uy, vy = nz * ux - nx * uz, vz = nx * uy - ny * ux;
        ll mxh = 0;
        for (int i = 0; i < n; i++) {
            P3 d = sub(p[i], p[f.a]);
            ll h = llabs(dot(nr, d)); mxh = max(mxh, h);
            q[i] = {d.x * ux + d.y * uy + d.z * uz, d.x * vx + d.y * vy + d.z * vz};
        }
        double h = mxh / nl;
        double r2 = mec(q);
        best = min(best, M_PI * r2 * h);
    }
    printf("%.8f\n", best);
}
