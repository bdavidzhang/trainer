#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
int main(){
    long long a; int m; scanf("%lld %d",&a,&m);
    vector<long long> pw(a+2); pw[0]=1; for(long long i=1;i<=a+1;i++) pw[i]=pw[i-1]*2%MOD;
    unordered_map<long long,long long> cnt; cnt.reserve(1<<22);
    while(m--){
        long long v; scanf("%lld",&v);
        long long sz;
        if(v==0) sz=pw[a];
        else { int hb=63-__builtin_clzll(v); long long e=a-1-hb; sz = e<0?0:pw[e]; }
        long long ans=sz;
        auto it=cnt.find(v); if(it!=cnt.end()) ans=((ans-it->second)%MOD+MOD)%MOD;
        printf("%lld\n",ans);
        if(ans){
            long long prev=-1;
            for(int k=0;k<=31;k++){
                long long u=v&((1LL<<k)-1);
                if(u==v) break;
                if(u==prev) continue;
                prev=u;
                long long &c=cnt[u]; c=(c+ans)%MOD;
            }
        }
    }
}
