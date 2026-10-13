#include <bits/stdc++.h>
using namespace std;
int main(){int U,n;cin>>U>>n;vector<string>w(n);for(auto&s:w)cin>>s;
 auto lcs=[&](const string&a,const string&b){int best=0;for(size_t i=0;i<a.size();i++)for(size_t j=0;j<b.size();j++){int k=0;while(i+k<a.size()&&j+k<b.size()&&a[i+k]==b[j+k])k++;best=max(best,k);}return best;};
 vector<vector<int>>c(n,vector<int>(n));
 for(int i=0;i<n;i++)for(int j=0;j<n;j++){int L=w[j].size(),s=lcs(w[i],w[j]);c[i][j]=L*(L+1)/2-s*(s+1)/2;}
 const int INF=1e9;vector<vector<int>>dp(1<<n,vector<int>(n,INF));dp[1][0]=0;int ans=1;
 for(int m=1;m<(1<<n);m++)for(int l=0;l<n;l++){int d=dp[m][l];if(d>U)continue;ans=max(ans,__builtin_popcount(m));
  for(int j=0;j<n;j++)if(!(m>>j&1)){int&t=dp[m|1<<j][j];t=min(t,d+c[l][j]);}}
 printf("%d\n",ans);}
