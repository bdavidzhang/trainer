#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<long long> d(n),r(n);
    for(int i=0;i<n;i++) scanf("%lld %lld",&d[i],&r[i]);
    vector<int> dp(n,1); int best=0;
    for(int j=0;j<n;j++){
        for(int i=0;i<j;i++) if(d[j]-d[i]>r[i] && d[j]-d[i]>r[j]) dp[j]=max(dp[j],dp[i]+1);
        best=max(best,dp[j]);
    }
    printf("%d\n",n-best);
}
