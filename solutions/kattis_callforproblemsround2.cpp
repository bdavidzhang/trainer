#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k; scanf("%d %d", &n, &k);
    set<int> s; for (int i = 0; i < n; i++) { int d; scanf("%d", &d); s.insert(d); }
    printf("%d\n", min(k, (int)s.size()));
}
