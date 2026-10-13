#include <bits/stdc++.h>
using namespace std;
int main(){int n,k;scanf("%d %d",&n,&k);vector<double>p(n);for(auto&x:p)scanf("%lf",&x);
sort(p.rbegin(),p.rend());vector<double> dp(n+2,0.0);dp[0]=1;double best=0;
for(int m=1;m<=n;m++){double q=p[m-1];for(int j=m;j>=0;j--){dp[j]=dp[j]*(1-q)+(j?dp[j-1]*q:0);}
 if(m>=k){double s=0;for(int j=(m+k+1)/2;j<=m;j++)s+=dp[j];best=max(best,s);}}
printf("%.9f\n",best);}
