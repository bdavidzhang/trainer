#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    const int INF=1e9;
    int c[26][26]; for(auto&r:c)for(auto&x:r)x=INF;
    for(int i=0;i<n;i++){char s[8];int w;scanf("%s %d",s,&w);c[s[0]-'a'][s[1]-'a']=w;}
    int h=(k+1)/2;
    vector<int> dp(26,0),nd(26);
    for(int i=1;i<h;i++){
        fill(nd.begin(),nd.end(),INF);
        for(int a=0;a<26;a++) if(dp[a]<INF) for(int b=0;b<26;b++)
            if(c[a][b]<INF&&c[b][a]<INF) nd[b]=min(nd[b],dp[a]+c[a][b]+c[b][a]);
        dp=nd;
    }
    int best=INF;
    for(int a=0;a<26;a++){
        if(dp[a]>=INF)continue;
        if(k%2==0){ if(c[a][a]<INF) best=min(best,dp[a]+c[a][a]); }
        else best=min(best,dp[a]);
    }
    printf("%d\n",best>=INF?-1:best);
}
