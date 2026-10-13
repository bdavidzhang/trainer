#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<long long> a(n); for(auto&x:a)scanf("%lld",&x);
    sort(a.begin(),a.end());
    vector<vector<long long>> dp(n,vector<long long>(n,0)),nd;
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)dp[i][j]=1;
    for(int c=3;c<=k;c++){
        nd.assign(n,vector<long long>(n,0));
        for(int i=0;i<n;i++)for(int j=i+1;j<n;j++) if(dp[i][j])
            for(int l=j+1;l<n;l++) if(a[l]<=a[i]+a[j]) nd[j][l]+=dp[i][j];
        dp=nd;
    }
    long long r=0; for(auto&v:dp)for(auto x:v)r+=x;
    printf("%lld\n",r);
}
