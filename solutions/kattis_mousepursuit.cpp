#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<array<long long,4>> e(n);char buf[16];
for(auto&x:e){scanf("%s %lld %lld %lld",buf,&x[1],&x[2],&x[3]);x[0]=buf[0]=='C'?1:-1;}
long long k;scanf("%lld",&k);long long c=0,g=0;for(auto&x:e)if(x[1]<k){c+=x[0]*x[2];g+=x[0]*x[3];}
printf("%lld %lld\n",c,g);}
