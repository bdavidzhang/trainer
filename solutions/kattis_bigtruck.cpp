#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int>t(n);for(auto&x:t)scanf("%d",&x);int m;scanf("%d",&m);
 vector<vector<pair<int,int>>>g(n);for(int i=0;i<m;i++){int a,b,d;scanf("%d %d %d",&a,&b,&d);a--;b--;g[a].push_back({b,d});g[b].push_back({a,d});}
 const int INF=1e9;vector<int>d(n,INF),it(n,-1);vector<bool>done(n,false);d[0]=0;it[0]=t[0];
 for(int r=0;r<n;r++){int u=-1;for(int i=0;i<n;i++)if(!done[i]&&d[i]<INF&&(u<0||d[i]<d[u]||(d[i]==d[u]&&it[i]>it[u])))u=i;if(u<0)break;done[u]=true;
  for(auto[v,w]:g[u]){if(d[u]+w<d[v]||(d[u]+w==d[v]&&it[u]+t[v]>it[v])){d[v]=d[u]+w;it[v]=it[u]+t[v];}}}
 if(d[n-1]>=INF)puts("impossible");else printf("%d %d\n",d[n-1],it[n-1]);}
