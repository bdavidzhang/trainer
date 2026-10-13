#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=LLONG_MAX/4;
int main(){int n,m;scanf("%d %d",&n,&m);vector<vector<pair<int,int>>>g(n+1);
 for(int i=0;i<m;i++){int a,b,t;scanf("%d %d %d",&a,&b,&t);g[a].push_back({b,t});g[b].push_back({a,t});}
 vector<int>c(7);for(auto&x:c)scanf("%d",&x);
 sort(c.begin(),c.end());c.erase(unique(c.begin(),c.end()),c.end());
 int k=c.size();vector<int>src=c;src.push_back(1);
 vector<vector<ll>>D(k+1,vector<ll>(k+1));
 for(int s=0;s<=k;s++){vector<ll>d(n+1,INF);priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>>pq;d[src[s]]=0;pq.push({0,src[s]});
  while(!pq.empty()){auto [du,u]=pq.top();pq.pop();if(du>d[u])continue;for(auto [v,w]:g[u])if(du+w<d[v]){d[v]=du+w;pq.push({d[v],v});}}
  for(int j=0;j<=k;j++)D[s][j]=d[src[j]];}
 vector<int>p(k);iota(p.begin(),p.end(),0);ll best=INF;
 do{ll s=0;int cur=k;bool ok=1;for(int i=0;i<k;i++){if(D[cur][p[i]]>=INF){ok=0;break;}s+=D[cur][p[i]];cur=p[i];}if(ok)best=min(best,s);}while(next_permutation(p.begin(),p.end()));
 printf("%lld\n",best>=INF?-1:best);}
