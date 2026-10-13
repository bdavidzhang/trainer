#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,c; scanf("%d %d",&n,&c); vector<int> w(n); for(auto&x:w)scanf("%d",&x); sort(w.begin(),w.end());
    vector<long long> pre(n+1,0); for(int i=0;i<n;i++)pre[i+1]=pre[i]+w[i];
    static bitset<100001> B; B[0]=1; long long best=LLONG_MAX;
    if(pre[n]<=c) best=pre[n];
    for(int i=n-1;i>=0;i--){
        // smallest unpacked item is i; items <i all packed, subset of items >i packed
        if(pre[i]<=c){
            long long lo=max(0LL,(long long)c-w[i]-pre[i]+1), hi=c-pre[i];
            for(long long s=lo;s<=hi;s++) if(B[s]){best=min(best,pre[i]+s);break;}
        }
        B|=B<<w[i];
    }
    printf("%lld\n",best);
}
