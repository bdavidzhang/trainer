#include <bits/stdc++.h>
using namespace std;
int main(){int t;scanf("%d",&t);while(t--){int n;long long p;scanf("%d %lld",&n,&p);long long s=0;for(int i=0;i<n;i++){long long x;scanf("%lld",&x);s+=x;}printf("%.10Lf\n",(long double)p*p/(long double)s);}}
