#include <bits/stdc++.h>
int main(){int p;scanf("%d",&p);while(p--){long long k,b;unsigned long long n;scanf("%lld %lld %llu",&k,&b,&n);long long r=0;while(n){long long d=n%b;r+=d*d;n/=b;}printf("%lld %lld\n",k,r);}}
