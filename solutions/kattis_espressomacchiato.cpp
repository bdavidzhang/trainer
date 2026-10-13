#include <bits/stdc++.h>
using namespace std;
// Anti-diagonal i+j==n-1: every monotone path crosses each anti-diagonal exactly once.
int main(){int t;scanf("%d",&t);while(t--){int n;scanf("%d",&n);for(int i=0;i<n;i++){string s(n,'.');s[n-1-i]='C';puts(s.c_str());}}}
