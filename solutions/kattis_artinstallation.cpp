#include <bits/stdc++.h>
using namespace std;
int main() {
    int r, g, b, cr, cg, cb, rg, gb;
    scanf("%d %d %d %d %d %d %d %d", &r, &g, &b, &cr, &cg, &cb, &rg, &gb);
    int nr = max(0, r - cr), ng = max(0, g - cg), nb = max(0, b - cb);
    // red can only come from RG, blue only from GB; green takes whatever is left of both
    if (nr > rg || nb > gb || ng > (rg - nr) + (gb - nb)) { puts("-1"); return 0; }
    printf("%d\n", nr + ng + nb);
}
