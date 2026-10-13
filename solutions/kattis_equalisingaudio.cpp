#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; long long x;
    scanf("%d %lld",&n,&x);
    vector<long long> a(n); long double s=0;
    for(auto&v:a){scanf("%lld",&v); s+=(long double)v*v;}
    long double f = s>0 ? sqrtl((long double)x*n/s) : 0;
    for(int i=0;i<n;i++) printf("%.10Lf%c",(long double)a[i]*f," \n"[i==n-1]);
}
