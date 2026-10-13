#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    int n;
    scanf("%d", &n);
    vector<ll> a(n + 1);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    a[n] = -1;
    vector<int> L(n), R(n), st;
    for (int i = 0; i <= n; i++) {
        while (!st.empty() && a[st.back()] > a[i]) { R[st.back()] = i - 1; st.pop_back(); }
        if (i < n) st.push_back(i);
    }
    st.clear();
    for (int i = n - 1; i >= -1; i--) {
        while (!st.empty() && (i < 0 || a[st.back()] > a[i])) { L[st.back()] = i + 1; st.pop_back(); }
        if (i >= 0) st.push_back(i);
    }
    ll best = -1; int bs = 0, be = 0;
    for (int i = 0; i < n; i++) {
        ll r = a[i] * (R[i] - L[i] + 1);
        if (r > best || (r == best && (L[i] < bs || (L[i] == bs && R[i] < be)))) { best = r; bs = L[i]; be = R[i]; }
    }
    printf("%d %d %lld\n", bs + 1, be + 1, best);
}
