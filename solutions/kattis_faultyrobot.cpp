#include <bits/stdc++.h>
using namespace std;
int n,m;int f[1005];vector<int> adj[1005];bool stopn[1005];
// follow forced moves from u; mark the stop node if any; return visited path
vector<int> follow(int u){vector<int> path;vector<char> vis(n+1,0);
  while(true){if(vis[u])break;vis[u]=1;path.push_back(u);if(!f[u]){stopn[u]=true;break;}u=f[u];}
  return path;}
int main(){scanf("%d %d",&n,&m);for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);if(a<0){a=-a;f[a]=b;}adj[a].push_back(b);}
  vector<int> p=follow(1);
  for(int u:p)for(int v:adj[u])follow(v);
  int c=0;for(int i=1;i<=n;i++)c+=stopn[i];printf("%d\n",c);}
