#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n,m,k1,k2;scanf("%d %d %d %d",&n,&m,&k1,&k2);
 vector<vector<array<int,3>>> g(n);
 for(int i=0;i<m;i++){int u,v,x,c;scanf("%d %d %d %d",&u,&v,&x,&c);u--;v--;g[u].push_back({v,x,c});g[v].push_back({u,x,c});}
 int s,t;scanf("%d %d",&s,&t);s--;t--;
 int A=k1+1,B=k2+1;auto id=[&](int v,int r,int b){return (v*A+r)*B+b;};
 vector<ll> d((size_t)n*A*B,LLONG_MAX);
 priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
 d[id(s,0,0)]=0;pq.push({0,id(s,0,0)});
 while(!pq.empty()){auto [dd,st]=pq.top();pq.pop();if(dd>d[st])continue;int b=st%B,r=st/B%A,v=st/B/A;
  if(v==t&&r==k1&&b==k2)break;
  for(auto&e:g[v]){int nr=r+(e[2]==1),nb=b+(e[2]==2);if(nr>k1||nb>k2)continue;int ns=id(e[0],nr,nb);if(dd+e[1]<d[ns]){d[ns]=dd+e[1];pq.push({d[ns],ns});}}}
 ll r=d[id(t,k1,k2)];printf("%lld\n",r==LLONG_MAX?-1:r);}
