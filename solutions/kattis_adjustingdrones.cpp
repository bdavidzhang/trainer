#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, k;
        scanf("%d %d", &n, &k);
        int R = 3 * n + 3;
        vector<int> c(R + 1, 0);
        for (int i = 0; i < n; i++) { int a; scanf("%d", &a); c[a]++; }
        // each value v with c[v]>1 emits a packet of size c[v]-1 moving right at speed 1,
        // dropping one unit in every empty cell it is the first to reach.
        vector<pair<int,int>> st; // (origin, remaining)
        int ans = 0;
        for (int w = 1; w <= R; w++) {
            if (c[w] == 0) {
                if (!st.empty()) {
                    auto &p = st.back();
                    p.second--;
                    if (p.second == k - 1) ans = max(ans, w - p.first);
                    if (p.second == 0) st.pop_back();
                }
            } else if (c[w] > 1) st.push_back({w, c[w] - 1});
        }
        printf("%d\n", ans);
    }
}
