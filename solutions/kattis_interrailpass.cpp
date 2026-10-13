#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<long long> t(n+1),f(n+1);
    for(int i=1;i<=n;i++)scanf("%lld %lld",&t[i],&f[i]);
    vector<long long> p(k),d(k),c(k);
    for(int j=0;j<k;j++)scanf("%lld %lld %lld",&p[j],&d[j],&c[j]);
    vector<long long> dp(n+1,0);
    vector<int> ptr(k,1);
    for(int e=1;e<=n;e++){
        long long b=dp[e-1]+f[e];
        for(int j=0;j<k;j++){
            int &i=ptr[j];
            while(i<e && (i<e-d[j]+1 || t[i]+p[j]-1<t[e])) i++;
            b=min(b,dp[i-1]+c[j]);
        }
        dp[e]=b;
    }
    printf("%lld\n",dp[n]);
}
