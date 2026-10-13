#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<long long> c(n+2,0);
    for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
    vector<int> ms(n+2,0); // ms[e]=max start among intervals ending at e
    for(int i=0;i<m;i++){int s,e;scanf("%d %d",&s,&e);ms[e]=max(ms[e],s);}
    // dp[i]: min cost, i is last visited day, all intervals with end<i stabbed. dp[0]=0.
    vector<long long> dp(n+2,0);
    deque<int> dq; dq.push_back(0);
    int L=0; // max start among intervals with end < i
    for(int i=1;i<=n+1;i++){
        L=max(L,ms[i-1]);
        while(!dq.empty()&&dq.front()<L)dq.pop_front();
        dp[i]=dp[dq.front()]+c[i];
        while(!dq.empty()&&dp[dq.back()]>=dp[i])dq.pop_back();
        dq.push_back(i);
    }
    printf("%lld\n",dp[n+1]);
}
