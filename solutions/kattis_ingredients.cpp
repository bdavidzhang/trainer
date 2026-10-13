#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int B,n;if(scanf("%d %d",&B,&n)!=2)return 0;
 unordered_map<string,int>id;id.reserve(1<<15);
 vector<array<int,4>>rec(n);
 char s1[64],s2[64],s3[64];
 auto get=[&](const char*s){auto it=id.find(s);if(it!=id.end())return it->second;int k=id.size();id.emplace(s,k);return k;};
 for(int i=0;i<n;i++){int c,p;scanf("%63s %63s %63s %d %d",s1,s2,s3,&c,&p);int d=get(s1),b=get(s2);rec[i]={b,d,c,p};}
 int V=id.size();
 vector<int>head(V+1,0),indeg(V,0);
 for(auto&r:rec){head[r[0]+1]++;indeg[r[1]]++;}
 for(int i=0;i<V;i++)head[i+1]+=head[i];
 vector<int>pos(head.begin(),head.begin()+V),adj(n);
 for(int i=0;i<n;i++)adj[pos[rec[i][0]]++]=i;
 const ll INF=LLONG_MAX/4;
 vector<ll>cost(V,INF),pres(V,0);
 vector<int>q;
 for(int i=0;i<V;i++)if(!indeg[i]){cost[i]=0;pres[i]=0;q.push_back(i);}
 for(size_t h=0;h<q.size();h++){int u=q[h];
  for(int e=head[u];e<head[u+1];e++){auto&r=rec[adj[e]];int v=r[1];ll c=cost[u]+r[2],p=pres[u]+r[3];
   if(c<cost[v]||(c==cost[v]&&p>pres[v])){cost[v]=c;pres[v]=p;}
   if(--indeg[v]==0)q.push_back(v);}}
 vector<ll>dp(B+1,0);
 for(int i=0;i<V;i++){if(cost[i]>B||pres[i]==0)continue;int c=cost[i];ll p=pres[i];
  for(int j=B;j>=c;j--)if(dp[j-c]+p>dp[j])dp[j]=dp[j-c]+p;}
 int mc=0;while(dp[mc]!=dp[B])mc++;
 printf("%lld\n%d\n",dp[B],mc);}
