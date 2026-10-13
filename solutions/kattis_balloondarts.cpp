#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
static bool col(const P&a,const P&b,const P&c){
 __int128 v=(__int128)(b.first-a.first)*(c.second-a.second)-(__int128)(b.second-a.second)*(c.first-a.first);return v==0;}
static bool rec(const vector<P>&v,int k){
 if((int)v.size()<=2*k)return true;
 if(k==0)return false;
 for(int i=0;i<=k;i++)for(int j=i+1;j<=k;j++){
  vector<P> r;for(auto&p:v)if(!col(v[i],v[j],p))r.push_back(p);
  if(rec(r,k-1))return true;}
 return false;}
int main(){int n;scanf("%d",&n);vector<P> v(n);for(auto&p:v)scanf("%lld %lld",&p.first,&p.second);
 puts(rec(v,3)?"possible":"impossible");}
