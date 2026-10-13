#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){ int n; ll c; scanf("%d %lld",&n,&c); ll A=LLONG_MIN,B=LLONG_MIN; 
    for(int i=1;i<=n;i++){ ll x; scanf("%lld",&x); A=max(A,-x+c*i); B=max(B,x+c*i); printf("%lld%c",max(x-c*i+A,-x-c*i+B)," \n"[i==n]); } }
