#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> g(m); vector<char> has(n + 2, 0);
    for (auto& x : g) scanf("%d", &x), has[x] = 1;
    int cur = 1;
    string out;
    for (int x : g) {
        for (; cur < x; cur++) if (!has[cur]) out += to_string(cur) + "\n";
        out += to_string(x) + "\n";
    }
    for (; cur <= n; cur++) if (!has[cur]) out += to_string(cur) + "\n";
    fputs(out.c_str(), stdout);
}
