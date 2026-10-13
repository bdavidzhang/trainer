#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> pg(n + 1), par(n + 1, 0), d(n + 1, 0);
    vector<bool> leaf(n + 1, true);
    for (int i = 1; i <= n; i++) scanf("%d", &pg[i]);
    for (int i = 0; i < m; i++) { int a, b; scanf("%d %d", &a, &b); par[b] = a; leaf[a] = false; }
    for (int i = 1; i <= n; i++) d[i] = d[par[i]] + pg[i]; // parent index is smaller
    vector<int> L;
    for (int i = 1; i <= n; i++) if (leaf[i]) L.push_back(i);
    int best = INT_MAX;
    for (size_t i = 0; i < L.size(); i++) for (size_t j = i + 1; j < L.size(); j++) {
        int a = L[i], b = L[j];
        while (a != b) { if (a > b) a = par[a]; else b = par[b]; }
        best = min(best, d[L[i]] + d[L[j]] - d[a]);
    }
    printf("%d\n", best);
}
