#include <bits/stdc++.h>
using namespace std;
int main() {
    int s; cin >> s; int a;
    if (s > 0) a = (s == 1 ? 2 : 1);
    else if (s < 0) a = (s == -1 ? -2 : -1);
    else a = 1;
    cout << a << " " << s - a << "\n";
}
