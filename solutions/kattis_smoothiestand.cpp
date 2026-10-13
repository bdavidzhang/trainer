#include <bits/stdc++.h>
using namespace std;
int main(){int k,r;scanf("%d %d",&k,&r);vector<long long>h(k);for(auto&x:h)scanf("%lld",&x);
long long best=0;for(int i=0;i<r;i++){long long m=LLONG_MAX;for(int j=0;j<k;j++){long long a;scanf("%lld",&a);if(a>0)m=min(m,h[j]/a);}
long long p;scanf("%lld",&p);if(m==LLONG_MAX)m=0;best=max(best,m*p);}
printf("%lld\n",best);}
