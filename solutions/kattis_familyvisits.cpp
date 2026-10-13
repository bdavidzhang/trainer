#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,d; scanf("%d %d",&n,&d);
    vector<int> m(n+1),c(n+1); vector<char> vis(n+1,0);
    for(int i=1;i<=n;i++)scanf("%d %d",&m[i],&c[i]);
    for(int i=0;i<d;i++){int v;scanf("%d",&v);vis[v]=1;}
    const int INF=INT_MAX/2;
    vector<int> dp(n+1,INF),nd(n+1); dp[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            int best=INF;
            if(dp[j]<INF) best=dp[j]+m[i];
            if(j>0&&dp[j-1]<INF) best=min(best,max(0,dp[j-1]+m[i]-c[i]));
            if(vis[i]&&best>0) best=INF;
            nd[j]=best;
        }
        dp=nd;
    }
    for(int j=0;j<=n;j++) if(dp[j]<INF){printf("%d\n",j);return 0;}
    puts("-1");
}
