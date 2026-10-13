#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int S;scanf("%d",&S);vector<array<ll,4>> L(S);for(auto&l:L)scanf("%lld %lld %lld %lld",&l[0],&l[1],&l[2],&l[3]);
 int T;scanf("%d",&T);while(T--){ll a,b,c,d;scanf("%lld %lld %lld %lld",&a,&b,&c,&d);int cnt=0;
  for(auto&l:L){ll dx=l[2]-l[0],dy=l[3]-l[1];ll s1=dx*(b-l[1])-dy*(a-l[0]),s2=dx*(d-l[1])-dy*(c-l[0]);if((s1>0)!=(s2>0))cnt++;}
  puts(cnt&1?"different":"same");}}
