#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<vector<pair<int,int>>> at(k+1);
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){int x;scanf("%d",&x);at[x].push_back({i,j});}
    const long long INF=LLONG_MAX/4;
    vector<long long> dp(at[1].size(),0);
    for(int v=2;v<=k;v++){
        vector<long long> nd(at[v].size(),INF);
        for(size_t b=0;b<at[v].size();b++)
            for(size_t a=0;a<at[v-1].size();a++){
                if(dp[a]>=INF) continue;
                long long c=dp[a]+abs(at[v][b].first-at[v-1][a].first)+abs(at[v][b].second-at[v-1][a].second);
                nd[b]=min(nd[b],c);
            }
        dp.swap(nd);
    }
    long long best=INF;
    for(long long x:dp) best=min(best,x);
    printf("%lld\n",best>=INF?-1:best);
}
