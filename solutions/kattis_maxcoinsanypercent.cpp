#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n,m;scanf("%d %d",&n,&m);vector<ll>c(n);for(auto&x:c)scanf("%lld",&x);
vector<vector<int>> g(n);vector<pair<int,int>> ed(m);
for(auto&e:ed){scanf("%d %d",&e.first,&e.second);g[e.first].push_back(e.second);}
// iterative tarjan
vector<int> idx(n,-1),low(n,0),comp(n,-1),it(n,0),st,cs;int T=0,C=0;
for(int s=0;s<n;s++){if(idx[s]!=-1)continue;cs.push_back(s);idx[s]=low[s]=T++;st.push_back(s);
 while(!cs.empty()){int u=cs.back();
  if(it[u]<(int)g[u].size()){int v=g[u][it[u]++];
   if(idx[v]==-1){idx[v]=low[v]=T++;st.push_back(v);cs.push_back(v);}
   else if(comp[v]==-1)low[u]=min(low[u],idx[v]);}
  else{cs.pop_back();if(!cs.empty())low[cs.back()]=min(low[cs.back()],low[u]);
   if(low[u]==idx[u]){while(1){int v=st.back();st.pop_back();comp[v]=C;if(v==u)break;}C++;}}
 }}
// comp ids are in reverse topological order: edges go from higher id to lower id
vector<ll> w(C,0);for(int i=0;i<n;i++)w[comp[i]]+=c[i];
vector<vector<int>> cg(C);for(auto&e:ed){int a=comp[e.first],b=comp[e.second];if(a!=b)cg[a].push_back(b);}
const ll NEG=LLONG_MIN/4;vector<ll> dp(C,NEG);int t=comp[n-1];
// dp[x]=best weight path from x to t; process ids ascending (sinks first)
for(int x=0;x<C;x++){if(x==t)dp[x]=w[x];ll b=NEG;for(int y:cg[x])b=max(b,dp[y]);if(b>NEG)dp[x]=max(dp[x],b+w[x]);}
printf("%lld\n",dp[comp[0]]);}
