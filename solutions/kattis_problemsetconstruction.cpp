#include <bits/stdc++.h>
using namespace std;
int main(){int n,k,t;scanf("%d %d %d",&n,&k,&t);vector<double>p(n);vector<int>s(n);for(int i=0;i<n;i++)scanf("%lf %d",&p[i],&s[i]);
 vector<int>o(n);iota(o.begin(),o.end(),0);sort(o.begin(),o.end(),[&](int a,int b){return s[a]<s[b];});
 vector<vector<double>>C(n+1,vector<double>(n+1,0));for(int i=0;i<=n;i++){C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];}
 // dp[c][w]
 vector<vector<double>>dp(k+1,vector<double>(t+1,0));dp[0][0]=1;vector<double>ans(n);
 double tot=C[n-1][k-1];
 for(int r=0;r<n;r++){int i=o[r];int rem=n-1-r;double a=0;
  for(int c=0;c<=min(r,k-1);c++){int need=k-1-c;if(need>rem)continue;double sm=0;for(int w=0;w+s[i]<=t;w++)sm+=dp[c][w];a+=sm*C[rem][need];}
  ans[i]=p[i]*a/tot;
  for(int c=min(r,k-1);c>=0;c--){if(c+1>k)continue;for(int w=t;w>=0;w--){double v=dp[c][w];if(v==0)continue;
    if(c+1<=k){dp[c+1][w]+=v*(1-p[i]);if(w+s[i]<=t)dp[c+1][w+s[i]]+=v*p[i];}}}
 }
 for(int i=0;i<n;i++)printf("%.9f\n",ans[i]);}
