#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
double R, v, w, d, al;
// rotate in place by phi (CCW), then arc CCW of radius R, then straight
double eval(double phi) {
    double px = d * cos(al - phi), py = d * sin(al - phi);
    double D = hypot(px, py - R);
    if (D < R - 1e-9) return 1e18;
    if (D < R) D = R;
    double beta = atan2(py - R, px);
    double gam = beta - acos(min(1.0, R / D));
    double th = fmod(gam + PI / 2, 2 * PI);
    if (th < 0) th += 2 * PI;
    if (th > 2 * PI - 1e-9) th = 0;
    double b = sqrt(max(0.0, D * D - R * R));
    return (phi + th) / w + b / v;
}
int main() {
    double x, y;
    scanf("%lf %lf %lf %lf", &x, &y, &v, &w);
    R = v / w;
    d = hypot(x, y);
    double best = 1e18;
    for (int s = 0; s < 2; s++) {
        al = atan2(s ? -y : y, x);
        const int N = 400000;
        double step = 2 * PI / N;
        double bp = 0, bv = 1e18;
        for (int i = 0; i < N; i++) {
            double p = i * step, t = eval(p);
            if (t < bv) bv = t, bp = p;
        }
        double lo = max(0.0, bp - step), hi = min(2 * PI, bp + step);
        for (int it = 0; it < 100; it++) {
            double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
            double f1 = eval(m1), f2 = eval(m2);
            if (f1 < f2) hi = m2; else lo = m1;
            bv = min(bv, min(f1, f2));
        }
        if (d <= 2 * R) {
            double a = asin(min(1.0, d / (2 * R)));
            double c[2] = {al - a, al - PI + a};
            for (double p : c) {
                p = fmod(p, 2 * PI);
                if (p < 0) p += 2 * PI;
                bv = min(bv, eval(p));
                // on-circle: time is exactly (phi + arc)/w
            }
        }
        best = min(best, bv);
    }
    printf("%.8f\n", best);
}
