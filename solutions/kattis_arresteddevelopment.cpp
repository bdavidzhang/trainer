#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int>a(n),b(n);int S=0;
    for(int i=0;i<n;i++){scanf("%d %d",&a[i],&b[i]);S+=a[i];}
    const int INF=INT_MAX;
    vector<int> dp(S+1,INF);dp[0]=0;int cur=0;
    for(int i=0;i<n;i++){
        for(int s=cur;s>=0;s--){ if(dp[s]==INF)continue;
            int v=dp[s];
            if(v<dp[s+a[i]])dp[s+a[i]]=v;
            dp[s]=v+b[i];
        }
        cur+=a[i];
    }
    int ans=INF;for(int s=0;s<=S;s++)if(dp[s]!=INF)ans=min(ans,max(s,dp[s]));
    printf("%d\n",ans);}
