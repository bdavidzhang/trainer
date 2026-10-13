#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct E{int to,cap;ll cost;};
struct MCMF{int n;vector<E> es;vector<vector<int>> g;MCMF(int n):n(n),g(n){}
 void add(int a,int b,int c,ll w){g[a].push_back(es.size());es.push_back({b,c,w});g[b].push_back(es.size());es.push_back({a,0,-w});}
 ll run(int s,int t){ll res=0;while(true){vector<ll> d(n,LLONG_MAX);vector<int> pe(n,-1),inq(n,0);deque<int> q;d[s]=0;q.push_back(s);
  while(!q.empty()){int v=q.front();q.pop_front();inq[v]=0;for(int id:g[v]){E&e=es[id];if(e.cap>0&&d[v]+e.cost<d[e.to]){d[e.to]=d[v]+e.cost;pe[e.to]=id;if(!inq[e.to]){inq[e.to]=1;q.push_back(e.to);}}}}
  if(d[t]==LLONG_MAX)break;int f=INT_MAX;for(int v=t;v!=s;v=es[pe[v]^1].to)f=min(f,es[pe[v]].cap);
  for(int v=t;v!=s;v=es[pe[v]^1].to){es[pe[v]].cap-=f;es[pe[v]^1].cap+=f;}res+=(ll)f*d[t];}return res;}};
int main(){int n;scanf("%d",&n);vector<pair<ll,int>> p(n);for(auto&x:p)scanf("%lld %d",&x.first,&x.second);sort(p.begin(),p.end());
 ll ans[2];for(int sg=0;sg<2;sg++){MCMF f(2*n+2);int S=2*n,T=2*n+1;
  for(int i=0;i<n;i++){if(i<n-1)f.add(S,i,1,0);int cap=(i==n-1)?p[i].second:p[i].second-1;f.add(n+i,T,cap,0);
   for(int j=i+1;j<n;j++){ll w=p[i].first^p[j].first;f.add(i,n+j,1,sg?-w:w);}}
  ll r=f.run(S,T);ans[sg]=sg?-r:r;}
 printf("%lld %lld\n",ans[0],ans[1]);}
