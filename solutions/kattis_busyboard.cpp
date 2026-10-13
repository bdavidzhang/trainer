#include <bits/stdc++.h>
using namespace std;
int main() {
    int r, c;
    cin >> r >> c;
    vector<string> s(r), t(r);
    for (auto& x : s) cin >> x;
    for (auto& x : t) cin >> x;
    if (s == t) { puts("1"); return 0; }
    vector<int> rc(r, 0), cc(c, 0);
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) if (t[i][j] == 'X') rc[i]++, cc[j]++;
    // bad X: not alone in its row and column
    vector<char> rowBad(r, 0), colBad(c, 0);
    bool iso = false;
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) if (t[i][j] == 'X') {
        if (rc[i] == 1 && cc[j] == 1) iso = true;
        else rowBad[i] = colBad[j] = 1;
    }
    if (!iso) { puts("0"); return 0; }
    bool up = false;
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
        if (rowBad[i] && colBad[j]) { if (s[i][j] != t[i][j]) { puts("0"); return 0; } }
        if (!rowBad[i] && !colBad[j] && s[i][j] == 'O') up = true;
    }
    puts(up ? "1" : "0");
}
