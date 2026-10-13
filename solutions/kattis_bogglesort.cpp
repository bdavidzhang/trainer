#include <bits/stdc++.h>
using namespace std;
int main(){
    string r[6];
    for(auto&s:r)cin>>s;
    const int INF=1e9;
    vector<int> dp(26,INF);
    dp[0]=0; // last letter 'A'
    for(int i=0;i<16;i++){
        vector<int> nd(26,INF);
        for(int k=0;k<6;k++){
            int cost = k==0?0:(k==5?2:1);
            int c=r[k][i]-'A';
            int nl = (c=='Q'-'A')?('U'-'A'):c;
            int best=INF;
            for(int l=0;l<=c;l++)best=min(best,dp[l]);
            if(best<INF)nd[nl]=min(nd[nl],best+cost);
        }
        dp=nd;
    }
    int ans=*min_element(dp.begin(),dp.end());
    if(ans>=INF)puts("impossible");else printf("%d\n",ans);
}
