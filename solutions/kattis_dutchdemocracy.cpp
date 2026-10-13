#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<int> p(n); long long T=0;
    for(auto&v:p){ scanf("%d",&v); T+=v; }
    sort(p.rbegin(),p.rend());
    int H=(int)(T/2); // sums <= H are not a strict majority
    vector<unsigned long long> dp(H+1,0); dp[0]=1;
    unsigned long long ans=0;
    for(int i=0;i<n;i++){
        int v=p[i];
        // p[i] is the smallest member: others (larger, earlier) have sum s with s<=H and s+v>H
        for(int s=max(0,H-v+1); s<=H; s++) ans+=dp[s];
        for(int s=H; s>=v; s--) dp[s]+=dp[s-v];
    }
    printf("%llu\n",ans);
}
