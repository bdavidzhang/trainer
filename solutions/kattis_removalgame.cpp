#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    while(scanf("%d",&n)==1 && n){
        vector<int> a(2*n);
        for(int i=0;i<n;i++){scanf("%d",&a[i]);a[i+n]=a[i];}
        int N=2*n;
        vector<vector<int>> g(N,vector<int>(N)), dp(N,vector<int>(N,0));
        for(int i=0;i<N;i++)for(int j=0;j<N;j++)g[i][j]=std::gcd(a[i],a[j]);
        // dp[i][j]: min cost to remove everything strictly between i and j, keeping i and j
        for(int len=2;len<=n;len++)for(int i=0;i+len<N;i++){
            int j=i+len,b=INT_MAX;
            for(int k=i+1;k<j;k++)b=min(b,dp[i][k]+dp[k][j]);
            dp[i][j]=b+g[i][j];
        }
        int best=INT_MAX;
        for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)
            best=min(best,dp[i][j]+dp[j][i+n]+g[i][j]);
        printf("%d\n",best);
    }
}
