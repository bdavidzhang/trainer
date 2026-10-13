#include <bits/stdc++.h>
using namespace std;
struct E{int to;double l,v,w;};
int main(){int n,m;double t;scanf("%d %d %lf",&n,&m,&t);vector<vector<E>> g(n+1);
for(int i=0;i<m;i++){int x,y;double l,v,w;scanf("%d %d %lf %lf %lf",&x,&y,&l,&v,&w);g[x].push_back({y,l,v,w});g[y].push_back({x,l,v,w});}
vector<double> d(n+1,1e300);d[1]=0;priority_queue<pair<double,int>,vector<pair<double,int>>,greater<>> pq;pq.push({0,1});
while(!pq.empty()){auto [du,u]=pq.top();pq.pop();if(du>d[u])continue;if(u==n)break;
for(auto&e:g[u]){double a;if(du>=t)a=du+e.l/e.w;else if(du+e.l/e.v<=t)a=du+e.l/e.v;else a=t+(e.l-e.v*(t-du))/e.w;
if(a<d[e.to]){d[e.to]=a;pq.push({a,e.to});}}}
printf("%.9f\n",d[n]);}
