#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    vector<int> d(n); for (auto& x : d) scanf("%d", &x);
    // smallest sum is 3a, largest is 3c; try every b in between and compare the sum sets
    if (d[0] % 3 == 0 && d[n - 1] % 3 == 0) {
        int a = d[0] / 3, c = d[n - 1] / 3;
        for (int b = a + 1; b < c; b++) {
            int v[3] = {a, b, c}; set<int> s;
            for (int i = 0; i < 3; i++) for (int j = i; j < 3; j++) for (int k = j; k < 3; k++) s.insert(v[i] + v[j] + v[k]);
            if (vector<int>(s.begin(), s.end()) == d) { printf("%d %d %d\n", a, b, c); return 0; }
        }
    }
    return 0;
}
