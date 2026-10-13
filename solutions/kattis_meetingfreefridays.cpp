#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; long long t,k;
    scanf("%d %lld %lld",&n,&t,&k);
    vector<pair<int,int>> v(n); // (end,start)
    for(auto&p:v) scanf("%d %d",&p.second,&p.first);
    sort(v.begin(),v.end());
    const int INF=INT_MAX/2;
    // dp[i][j]: min total length choosing j disjoint meetings among first i
    vector<vector<int>> dp(n+1);
    dp[0].assign(1,0);
    vector<int> ends(n);
    for(int i=0;i<n;i++) ends[i]=v[i].first;
    for(int i=1;i<=n;i++){
        int s=v[i-1].second,e=v[i-1].first;
        int p=upper_bound(ends.begin(),ends.end(),s)-ends.begin(); // meetings with end<=s
        // p <= i-1
        const vector<int>&q=dp[p];
        vector<int> cur=dp[i-1];
        if(cur.size()<q.size()+1) cur.resize(q.size()+1,INF);
        for(size_t j=0;j<q.size();j++) if(q[j]<INF) cur[j+1]=min(cur[j+1],q[j]+(e-s));
        dp[i]=move(cur);
    }
    long long lim=t-k; int best=0;
    for(size_t j=0;j<dp[n].size();j++) if(dp[n][j]<=lim) best=j;
    printf("%d\n",best);
}
