#include <bits/stdc++.h>
using namespace std;
int main(){long long n,c;scanf("%lld %lld",&n,&c);long long q=0,bw=LLONG_MAX,bi=-1;
for(long long i=0;i<n;i++){long long a;scanf("%lld",&a);long long tot=q+a;long long w=tot/c;
if(i+w<=n-1&&w<bw){bw=w;bi=i;}
q=max(0LL,tot-c);}
if(bi<0)puts("impossible");else printf("%lld\n",bi);}
