#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int K;
struct BIT{vector<ll> t;void init(int n){t.assign(n+1,0);}void add(int i,ll v){for(i++;i<=K;i+=i&-i)t[i]+=v;}ll q(int i){ll s=0;for(i++;i>0;i-=i&-i)s+=t[i];return s;}};
int main(){int n;scanf("%d",&n);vector<int> side(n),fok(n),pc(n);vector<ll> P(n),A(n);
 char a[16],b[16];
 for(int i=0;i<n;i++){scanf("%15s %15s %lld %lld",a,b,&P[i],&A[i]);side[i]=a[0]=='b';fok[i]=b[0]=='f';}
 vector<ll> xs(P);sort(xs.begin(),xs.end());xs.erase(unique(xs.begin(),xs.end()),xs.end());K=xs.size();
 for(int i=0;i<n;i++)pc[i]=lower_bound(xs.begin(),xs.end(),P[i])-xs.begin();
 BIT bs,bb;bs.init(K);bb.init(K);ll totb=0;
 priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> sells; // (price,idx)
 priority_queue<pair<ll,int>> buys; // (price,-idx)
 vector<array<ll,3>> out;
 for(int i=0;i<n;i++){
  if(fok[i]){
   if(side[i]){ if(bs.q(pc[i])<A[i])continue; }
   else { ll av=totb-(pc[i]?bb.q(pc[i]-1):0); if(av<A[i])continue; }
  }
  if(side[i]){buys.push({P[i],-i});bb.add(pc[i],A[i]);totb+=A[i];}
  else {sells.push({P[i],i});bs.add(pc[i],A[i]);}
  while(!sells.empty()&&!buys.empty()&&sells.top().first<=buys.top().first){
   int s=sells.top().second,u=-buys.top().second;ll x=min(A[s],A[u]);
   out.push_back({s+1,u+1,x});
   A[s]-=x;A[u]-=x;bs.add(pc[s],-x);bb.add(pc[u],-x);totb-=x;
   if(!A[s])sells.pop(); if(!A[u])buys.pop();
  }
 }
 printf("%d\n",(int)out.size());
 for(auto&o:out)printf("%lld %lld %lld\n",o[0],o[1],o[2]);}
