#include <bits/stdc++.h>
using namespace std;
int main(){int n;long long H;scanf("%d %lld",&n,&H);long long tot=0;bool ok=true;
 for(int i=0;i<n;i++){long long d[3];scanf("%lld %lld %lld",d,d+1,d+2);long long b=LLONG_MAX;
  for(int v=0;v<3;v++)if(d[v]<=H)b=min(b,min(d[(v+1)%3],d[(v+2)%3]));
  if(b==LLONG_MAX)ok=false;else tot+=b;}
 if(ok)printf("%lld\n",tot);else puts("impossible");}
