#include <bits/stdc++.h>
using namespace std;
// Keep a rooted connected subtree of m=n-k nodes with fewest leaves. A subtree with L leaves is
// a union of L root paths; max size with L leaves = sum of the L longest chains of the
// long-path decomposition, and any smaller size is reachable by peeling leaves (never adds leaves).
static char ibuf[1<<25];
int main(){
    int n,k;
    if(scanf("%d %d",&n,&k)!=2) return 0;
    vector<int> par(n,-1),h(n,1),best(n,-1);
    for(int i=1;i<n;i++) scanf("%d",&par[i]);
    for(int i=n-1;i>=1;i--){
        int p=par[i];
        if(h[i]+1>h[p]){ h[p]=h[i]+1; best[p]=i; }
    }
    vector<int> cnt(n+2,0); // counting sort of chain lengths
    cnt[h[0]]++;
    for(int i=1;i<n;i++) if(best[par[i]]!=i) cnt[h[i]]++;
    long long m=n-k, sum=0; long long ans=0;
    for(int len=n; len>=1 && sum<m; len--){
        if(!cnt[len]) continue;
        long long need=(m-sum+len-1)/len;
        long long take=min<long long>(need,cnt[len]);
        sum+=take*len; ans+=take;
    }
    printf("%lld\n",ans);
}
