#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,f,s,t;vector<vector<pair<int,int>>>g;
vector<ll> dij(int src){vector<ll>d(n,LLONG_MAX/4);priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>>q;d[src]=0;q.push({0,src});
 while(!q.empty()){auto [du,u]=q.top();q.pop();if(du>d[u])continue;for(auto [v,c]:g[u])if(du+c<d[v]){d[v]=du+c;q.push({d[v],v});}}return d;}
int main(){scanf("%d %d %d %d %d",&n,&m,&f,&s,&t);g.resize(n);
 for(int i=0;i<m;i++){int a,b,c;scanf("%d %d %d",&a,&b,&c);g[a].push_back({b,c});g[b].push_back({a,c});}
 auto ds=dij(s),dt=dij(t);ll ans=ds[t];
 for(int i=0;i<f;i++){int u,v;scanf("%d %d",&u,&v);ans=min(ans,ds[u]+dt[v]);}
 printf("%lld\n",ans);}
