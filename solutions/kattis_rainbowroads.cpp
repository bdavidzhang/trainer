#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<vector<pair<int,int>>>g(n+1);
for(int i=0;i<n-1;i++){int a,b,c;scanf("%d %d %d",&a,&b,&c);g[a].push_back({c,b});g[b].push_back({c,a});}
vector<int>tin(n+1),tout(n+1),par(n+1,0),it(n+1,0);int T=0;vector<int>st={1};tin[1]=T++;
while(!st.empty()){int u=st.back();if(it[u]<(int)g[u].size()){int v=g[u][it[u]++].second;if(v==par[u])continue;par[v]=u;tin[v]=T++;st.push_back(v);}else{tout[u]=T-1;st.pop_back();}}
vector<int>df(n+2,0);auto mark=[&](int l,int r){if(l>r)return;df[l]++;df[r+1]--;};
for(int u=1;u<=n;u++){auto&v=g[u];sort(v.begin(),v.end());
 for(size_t i=0;i<v.size();){size_t j=i;while(j<v.size()&&v[j].first==v[i].first)j++;
  if(j-i>=2)for(size_t k=i;k<j;k++){int x=v[k].second;if(x==par[u]){mark(0,tin[u]-1);mark(tout[u]+1,n-1);}else mark(tin[x],tout[x]);}
  i=j;}}
for(int i=1;i<n;i++)df[i]+=df[i-1];
vector<int>res;for(int u=1;u<=n;u++)if(df[tin[u]]==0)res.push_back(u);
printf("%d\n",(int)res.size());for(int u:res)printf("%d\n",u);}
