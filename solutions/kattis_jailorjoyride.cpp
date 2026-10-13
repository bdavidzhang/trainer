#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=LLONG_MAX/4;
int n,m;ll d[305][305];vector<int>adj[305];
int lab[305][305];// lab[t][p]: index of candidate list for state (p,t)
vector<vector<int>>cands;int allc[305];
ll memo[305][305];char st[305][305];
ll go(int p,int t){ // returns INF if impossible
 if(st[p][t]==2)return memo[p][t];if(st[p][t]==1)return INF;
 st[p][t]=1;ll res;
 if(adj[t].size()==1)res=d[p][t];
 else{ll worst=0;for(int x:cands[lab[t][p]]){ll v=go(t,x);if(v>=INF){worst=INF;break;}worst=max(worst,v);}
  res=worst>=INF?INF:worst+d[p][t];}
 st[p][t]=2;return memo[p][t]=res;}
int main(){int p,t;scanf("%d %d %d %d",&n,&m,&p,&t);
 for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)d[i][j]=i==j?0:INF;
 vector<array<int,2>>E(m);
 for(int i=0;i<m;i++){int a,b;ll l;scanf("%d %d %lld",&a,&b,&l);E[i]={a,b};d[a][b]=d[b][a]=min(d[a][b],l);adj[a].push_back(b);adj[b].push_back(a);}
 for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)if(d[i][k]<INF)for(int j=1;j<=n;j++)if(d[i][k]+d[k][j]<d[i][j])d[i][j]=d[i][k]+d[k][j];
 // bridges
 vector<int>tin(n+1,0),low(n+1,0);int timer=0;vector<array<int,2>>br;
 function<void(int,int)>dfs=[&](int v,int par){tin[v]=low[v]=++timer;for(int w:adj[v]){if(w==par)continue;if(tin[w])low[v]=min(low[v],tin[w]);else{dfs(w,v);low[v]=min(low[v],low[w]);if(low[w]>tin[v])br.push_back({v,w});}}};
 dfs(1,0);
 auto furthest=[&](int t0,const vector<char>&in){ll best=-1;vector<int>r;for(int x=1;x<=n;x++)if(in[x]){if(d[t0][x]>best){best=d[t0][x];r.clear();}if(d[t0][x]==best)r.push_back(x);}return r;};
 vector<char>all(n+1,1);
 for(int v=1;v<=n;v++){cands.push_back(furthest(v,all));for(int q=1;q<=n;q++)lab[v][q]=(int)cands.size()-1;}
 for(auto&b:br)for(int s=0;s<2;s++){int v=b[s],u=b[1-s];
  vector<char>in(n+1,0);vector<int>q{v};in[v]=1;
  for(size_t i=0;i<q.size();i++){int x=q[i];for(int w:adj[x]){if(x==v&&w==u)continue;if(!in[w]){in[w]=1;q.push_back(w);}}}
  cands.push_back(furthest(v,in));for(int x=1;x<=n;x++)if(!in[x])lab[v][x]=(int)cands.size()-1;}
 ll r=go(p,t);if(r>=INF)puts("impossible");else printf("%lld\n",r);}
