#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);long long a[10][10];for(int i=0;i<n;i++)for(int j=0;j<n;j++)scanf("%lld",&a[i][j]);
 vector<long long> dp(1<<n,0);dp[0]=1;
 for(int m=0;m<(1<<n);m++){int r=__builtin_popcount(m);if(r>=n||!dp[m])continue;for(int j=0;j<n;j++)if(!(m>>j&1))dp[m|1<<j]+=dp[m]*a[r][j];}
 printf("%lld\n",dp[(1<<n)-1]);}
