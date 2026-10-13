#include <bits/stdc++.h>
using namespace std;
int main(){int n,L;long long B;scanf("%d %d %lld",&n,&L,&B);int S,D;scanf("%d %d",&S,&D);
vector<array<int,3>>ed(L);vector<vector<int>>g(n+1);vector<long long>pt;
vector<long long>X(L),Y(L);
for(int i=0;i<L;i++){int a,b;scanf("%d %d %lld %lld",&a,&b,&X[i],&Y[i]);ed[i]={a,b,0};g[a].push_back(i);pt.push_back(X[i]);pt.push_back(Y[i]+1);}
sort(pt.begin(),pt.end());pt.erase(unique(pt.begin(),pt.end()),pt.end());
long long ans=0;vector<int>vis(n+1,0),q;int stamp=0;
for(size_t k=0;k+1<pt.size();k++){long long v=pt[k];stamp++;q.clear();q.push_back(S);vis[S]=stamp;
 for(size_t h=0;h<q.size()&&vis[D]!=stamp;h++){int u=q[h];for(int id:g[u]){if(X[id]<=v&&v<=Y[id]){int w=ed[id][1];if(vis[w]!=stamp){vis[w]=stamp;q.push_back(w);}}}}
 if(vis[D]==stamp)ans+=pt[k+1]-pt[k];}
printf("%lld\n",ans);}
