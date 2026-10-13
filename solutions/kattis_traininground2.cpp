#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef long long ll;
int main(){
    int n; ll I,T; scanf("%d %lld %lld",&n,&I,&T);
    int W=(n+2)/64+2;
    vector<u64> g((size_t)(n+2)*W,0);
    auto row=[&](int a){return g.data()+(size_t)a*W;};
    row(0)[0]=1;
    for(int j=0;j<n;j++){
        ll il,ih,tl,th; scanf("%lld %lld %lld %lld",&il,&ih,&tl,&th);
        ll alo=max(0LL,il-I), ahi=min((ll)j,ih-I);
        ll blo=max(0LL,tl-T), bhiG=min((ll)j,th-T);
        if(alo>ahi||blo>bhiG) continue;
        for(int a=(int)ahi;a>=(int)alo;a--){
            ll bhi=min(bhiG,(ll)j-a);
            if(blo>bhi) continue;
            u64*r=row(a); u64*r2=row(a+1);
            int w0=blo>>6,w1=bhi>>6;
            for(int w=w1;w>=w0;w--){
                u64 mask=~0ULL;
                if(w==w0) mask&=(~0ULL)<<(blo&63);
                if(w==w1){int e=bhi&63; if(e!=63) mask&=((1ULL<<(e+1))-1);}
                u64 t=r[w]&mask;
                if(!t) continue;
                r2[w]|=t;
                r[w+1]|=t>>63;
                r[w]|=t<<1;
            }
        }
    }
    int best=0;
    for(int a=0;a<=n;a++){
        u64*r=row(a);
        for(int w=W-1;w>=0;w--) if(r[w]){ int b=w*64+63-__builtin_clzll(r[w]); best=max(best,a+b); break; }
    }
    printf("%d\n",best);
}
