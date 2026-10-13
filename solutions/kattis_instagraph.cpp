#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<ll> e(m);
    for (int i = 0; i < m; i++) { int u, v; scanf("%d %d", &u, &v); e[i] = (ll)u * (n + 1) + v; }
    sort(e.begin(), e.end());
    vector<int> cc(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u = e[i] / (n + 1), v = e[i] % (n + 1);
        if (!binary_search(e.begin(), e.end(), (ll)v * (n + 1) + u)) cc[v]++;
    }
    int best = 1;
    for (int v = 2; v <= n; v++) if (cc[v] > cc[best]) best = v;
    printf("%d %d\n", best, cc[best]);
}
