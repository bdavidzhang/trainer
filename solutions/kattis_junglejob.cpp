#include <bits/stdc++.h>
using namespace std;
const long long M=1e9+7;
int main(){int n;scanf("%d",&n);vector<int>p(n,-1);for(int i=1;i<n;i++)scanf("%d",&p[i]);
vector<vector<long long>>dp(n);vector<long long>ans(n+1,0);
// dp[v][k]: connected sets containing v inside subtree of v with k nodes (index 0 = "take nothing" used when merging)
for(int v=0;v<n;v++)dp[v]={0,1};
for(int v=n-1;v>=0;v--){
  for(size_t k=1;k<dp[v].size();k++)ans[k]=(ans[k]+dp[v][k])%M;
  if(v==0)break;
  int u=p[v];
  vector<long long>&a=dp[u],&b=dp[v];
  vector<long long>c(a.size()+b.size()-1,0);
  for(size_t i=1;i<a.size();i++){ if(!a[i])continue; c[i]=(c[i]+a[i])%M;
    for(size_t j=1;j<b.size();j++)c[i+j]=(c[i+j]+a[i]*b[j])%M;}
  a.swap(c);vector<long long>().swap(b);
}
for(int k=1;k<=n;k++)printf("%lld\n",ans[k]);}
