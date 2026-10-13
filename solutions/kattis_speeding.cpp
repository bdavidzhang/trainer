#include <bits/stdc++.h>
int main(){int n;scanf("%d",&n);long long pt,pd,b=0;scanf("%lld %lld",&pt,&pd);for(int i=1;i<n;i++){long long t,d;scanf("%lld %lld",&t,&d);b=std::max(b,(d-pd)/(t-pt));pt=t;pd=d;}printf("%lld\n",b);}
