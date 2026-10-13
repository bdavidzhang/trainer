#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int G,K,R;scanf("%d %d %d",&G,&K,&R);const ll INF=4e18;
 vector<vector<ll>> d(K,vector<ll>(K,INF));for(int i=0;i<K;i++)d[i][i]=0;
 for(int i=0;i<R;i++){int a,b;ll t;scanf("%d %d %lld",&a,&b,&t);a--;b--;d[a][b]=min(d[a][b],t);d[b][a]=min(d[b][a],t);}
 for(int k=0;k<K;k++)for(int i=0;i<K;i++)if(d[i][k]<INF)for(int j=0;j<K;j++)if(d[k][j]<INF&&d[i][k]+d[k][j]<d[i][j])d[i][j]=d[i][k]+d[k][j];
 vector<int> V(G);vector<ll> S(G),E(G),M(G),dp(G,-1);
 vector<array<ll,3>> ev; // time, kind(0=end,1=start), id
 for(int i=0;i<G;i++){scanf("%d %lld %lld %lld",&V[i],&S[i],&E[i],&M[i]);V[i]--;ev.push_back({E[i],0,i});ev.push_back({S[i],1,i});}
 sort(ev.begin(),ev.end());
 vector<vector<ll>> et(K),pm(K);ll ans=0;
 for(auto&x:ev){int i=x[2];
  if(x[1]==0){if(dp[i]<0)continue;int v=V[i];ll b=pm[v].empty()?dp[i]:max(pm[v].back(),dp[i]);et[v].push_back(E[i]);pm[v].push_back(b);}
  else{int v=V[i];ll b=-1;if(d[0][v]<=S[i])b=0;
   for(int u=0;u<K;u++){if(d[u][v]>S[i]||et[u].empty())continue;ll lim=S[i]-d[u][v];
    int p=upper_bound(et[u].begin(),et[u].end(),lim)-et[u].begin();if(p>0)b=max(b,pm[u][p-1]);}
   if(b>=0){dp[i]=b+M[i];ans=max(ans,dp[i]);}}
 }
 printf("%lld\n",ans);}
