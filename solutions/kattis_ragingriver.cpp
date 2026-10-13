#include <bits/stdc++.h>
using namespace std;
struct E{int to,cap,cost;};
vector<E> es; vector<vector<int>> g;
void add(int a,int b){g[a].push_back(es.size());es.push_back({b,1,1});g[b].push_back(es.size());es.push_back({a,0,-1});}
int main(){int P,R,L;scanf("%d %d %d",&P,&R,&L);int n=R+2,s=R,t=R+1;g.resize(n);
 for(int i=0;i<L;i++){int a,b;scanf("%d %d",&a,&b);if(a==-2)a=s;else if(a==-1)a=t;if(b==-2)b=s;else if(b==-1)b=t;add(a,b);add(b,a);}
 int flow=0,cost=0;
 while(flow<P){vector<int> d(n,INT_MAX),pe(n,-1);vector<char> in(n,0);deque<int> q;d[s]=0;q.push_back(s);
  while(!q.empty()){int u=q.front();q.pop_front();in[u]=0;for(int id:g[u]){E&e=es[id];if(e.cap>0&&d[u]+e.cost<d[e.to]){d[e.to]=d[u]+e.cost;pe[e.to]=id;if(!in[e.to]){in[e.to]=1;q.push_back(e.to);}}}}
  if(d[t]==INT_MAX)break;
  for(int v=t;v!=s;v=es[pe[v]^1].to){es[pe[v]].cap--;es[pe[v]^1].cap++;}
  flow++;cost+=d[t];}
 if(flow<P)printf("%d people left behind\n",P-flow);else printf("%d\n",cost);}
