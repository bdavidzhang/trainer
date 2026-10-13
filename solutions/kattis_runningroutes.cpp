#include <bits/stdc++.h>
using namespace std;
static int dp[502][502];
static char M[502][502];
int main(){int n;scanf("%d",&n);for(int i=0;i<n;i++)for(int j=0;j<n;j++){int x;scanf("%d",&x);M[i][j]=x;}
 // dp[i][j] over half-open [i,j)
 for(int len=2;len<=n;len++)for(int i=0;i+len<=n;i++){int j=i+len;int b=dp[i+1][j];
  for(int k=i+1;k<j;k++)if(M[i][k]){int v=1+dp[i+1][k]+dp[k+1][j];if(v>b)b=v;}
  dp[i][j]=b;}
 printf("%d\n",dp[0][n]);}
