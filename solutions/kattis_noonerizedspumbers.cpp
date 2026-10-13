#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    string s[3], op, eq;
    cin >> s[0] >> op >> s[1] >> eq >> s[2];
    for (int a = 0; a < 3; a++) for (int b = a + 1; b < 3; b++)
        for (size_t i = 1; i < s[a].size(); i++) for (size_t j = 1; j < s[b].size(); j++) {
            string t[3] = {s[0], s[1], s[2]};
            t[a] = s[b].substr(0, j) + s[a].substr(i);
            t[b] = s[a].substr(0, i) + s[b].substr(j);
            bool ok = true;
            ll v[3];
            for (int k = 0; k < 3; k++) {
                if (t[k].size() > 10) { ok = false; break; }
                v[k] = stoll(t[k]);
                if (v[k] >= (1LL << 31)) ok = false;
            }
            if (!ok) continue;
            ll r = op == "+" ? v[0] + v[1] : v[0] * v[1];
            if (r == v[2]) {
                cout << t[0] << " " << op << " " << t[1] << " = " << t[2] << "\n";
                return 0;
            }
        }
}
