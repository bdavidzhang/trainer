#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    const long long INF=LLONG_MAX/4;
    vector<long long> dp(n+2,INF); dp[1]=0;
    for(int i=1;i<=n;i++){
        long long c; scanf("%lld",&c);
        int k=min(m,n-i+1);
        for(int j=1;j<=k;j++){
            long long r; scanf("%lld",&r);
            if(dp[i]<INF) dp[i+j]=min(dp[i+j],dp[i]+c-r);
        }
    }
    printf("%lld\n",dp[n+1]);
}
