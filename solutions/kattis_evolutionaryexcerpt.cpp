#include <bits/stdc++.h>
using namespace std;
static char A[1000005],Bs[1000005];
static int dp[260][260];
int main(){int n;scanf("%d",&n);scanf("%s",A);scanf("%s",Bs);
 const int W=250;string out;out.reserve(n);
 for(int s=0;s<n;s+=W){int len=min(W,n-s);const char*a=A+s,*b=Bs+s;
  for(int i=0;i<=len;i++)dp[i][len]=dp[len][i]=0;
  for(int i=len-1;i>=0;i--)for(int j=len-1;j>=0;j--)dp[i][j]=a[i]==b[j]?dp[i+1][j+1]+1:max(dp[i+1][j],dp[i][j+1]);
  int i=0,j=0;while(i<len&&j<len){if(a[i]==b[j]){out+=a[i];i++;j++;}else if(dp[i+1][j]>=dp[i][j+1])i++;else j++;}}
 puts(out.c_str());}
