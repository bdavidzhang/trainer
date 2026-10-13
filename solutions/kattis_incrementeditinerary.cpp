#include <bits/stdc++.h>
using namespace std;
int n,m;vector<vector<int>>g;
vector<int> bfs(int s){vector<int>d(n+1,-1);queue<int>q;q.push(s);d[s]=0;while(!q.empty()){int u=q.front();q.pop();for(int v:g[u])if(d[v]<0){d[v]=d[u]+1;q.push(v);}}return d;}
int main(){scanf("%d %d",&n,&m);g.resize(n+1);vector<pair<int,int>>e(m);for(auto&x:e){scanf("%d %d",&x.first,&x.second);g[x.first].push_back(x.second);g[x.second].push_back(x.first);}
auto d1=bfs(1),dn=bfs(n);int D=d1[n];bool ok=false;
for(auto&x:e){int u=x.first,v=x.second;if(d1[u]<0||d1[v]<0||d1[u]!=d1[v])continue;if(d1[u]+dn[u]==D||d1[v]+dn[v]==D)ok=true;}
puts(ok?"possible":"impossible");}
