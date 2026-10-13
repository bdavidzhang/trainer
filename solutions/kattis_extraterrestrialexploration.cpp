#include <bits/stdc++.h>
using namespace std;
map<int,long long> cache_;
long long ask(int i){
    auto it=cache_.find(i); if(it!=cache_.end())return it->second;
    printf("? %d\n",i); fflush(stdout);
    long long v; if(scanf("%lld",&v)!=1) exit(0);
    return cache_[i]=v;
}
int main(){
    int n; if(scanf("%d",&n)!=1)return 0;
    if(n==3){ printf("! 1 2 3\n"); fflush(stdout); return 0; }
    long long a=ask(1), c=ask(n), s=a+c;
    // first index in [2,n-1] with 2*o >= s, or n if none
    int lo=2, hi=n; // answer in [lo,hi]
    while(lo<hi){
        int mid=(lo+hi)/2; // mid<=n-1
        if(2*ask(mid)>=s) hi=mid; else lo=mid+1;
    }
    int best=-1; long long bd=LLONG_MAX;
    for(int cand: {lo-1, lo}){
        if(cand<2||cand>n-1)continue;
        long long d=llabs(2*ask(cand)-s);
        if(d<bd){bd=d;best=cand;}
    }
    printf("! 1 %d %d\n",best,n); fflush(stdout);
}
