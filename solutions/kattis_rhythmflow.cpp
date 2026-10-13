#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;scanf("%d %d",&n,&m);vector<long long>e(n),a(m);for(auto&x:e)scanf("%lld",&x);for(auto&x:a)scanf("%lld",&x);
 vector<vector<int>> dp(n+1,vector<int>(m+1,0));
 for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
  long long d=llabs(e[i-1]-a[j-1]);int s=d<=15?7:d<=23?6:d<=43?4:d<=102?2:0;
  dp[i][j]=max({dp[i-1][j],dp[i][j-1],dp[i-1][j-1]+s});}
 printf("%d\n",dp[n][m]);}
