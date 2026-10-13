#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n; int mx = 0;
    while (n--) {
        string s; cin >> s;
        if (s == "/") cout << (mx / 10 + 1) * 10 << "\n";
        else { int v = stoi(s); mx = max(mx, v); cout << v << "\n"; }
    }
}
