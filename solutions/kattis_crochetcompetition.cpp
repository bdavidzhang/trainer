#include <bits/stdc++.h>
using namespace std;
int rd() {
    string w, t; cin >> w >> t;
    const char *d[] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
    int di = 0; for (int i = 0; i < 7; i++) if (w == d[i]) di = i;
    return di * 1440 + stoi(t.substr(0, 2)) * 60 + stoi(t.substr(3, 2));
}
int main() {
    int a = rd(), b = rd();
    int d = ((b - a) % 10080 + 10080) % 10080;
    if (d == 0) d = 10080;
    int v[3] = {d / 1440, d % 1440 / 60, d % 60};
    const char *nm[3] = {"day", "hour", "minute"};
    vector<string> parts;
    for (int i = 0; i < 3; i++) if (v[i]) parts.push_back(to_string(v[i]) + " " + nm[i] + (v[i] > 1 ? "s" : ""));
    string out;
    if (parts.size() == 1) out = parts[0];
    else if (parts.size() == 2) out = parts[0] + " and " + parts[1];
    else out = parts[0] + ", " + parts[1] + ", " + parts[2];
    cout << out << "\n";
}
