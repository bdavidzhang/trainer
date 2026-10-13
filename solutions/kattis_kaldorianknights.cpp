#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
int main(){
    int n,h; scanf("%d %d",&n,&h);
    vector<long long> f(n+1,1);
    for(int i=1;i<=n;i++) f[i]=f[i-1]*i%MOD;
    vector<int> s(h+1,0);
    for(int i=1;i<=h;i++){ int k; scanf("%d",&k); s[i]=s[i-1]+k; }
    vector<long long> dp(h+1,0);
    long long ans=f[n];
    for(int l=1;l<=h;l++){
        unsigned long long acc=0;
        for(int j=1;j<l;j++){
            acc+=(unsigned long long)dp[j]*f[s[l]-s[j]];
            if((j&7)==0) acc%=MOD;
        }
        dp[l]=((f[s[l]]-(long long)(acc%MOD))%MOD+MOD)%MOD;
        ans=(ans-dp[l]*f[n-s[l]])%MOD;
    }
    printf("%lld\n",(ans%MOD+MOD)%MOD);
}
