#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef unsigned long long ull;
const ll MOD=1000000007;
const int B=15;
static ll lo[1<<B], hi[1<<B];
ll pw(ll b,ll e){ll r=1;b%=MOD;while(e){if(e&1)r=r*b%MOD;b=b*b%MOD;e>>=1;}return r;}
vector<pair<ll,ll>> divphi(ll n){ // (divisor, phi(divisor))
    vector<pair<ll,ll>> res{{1,1}};
    for(ll p=2;p*p<=n;p++) if(n%p==0){
        int e=0; while(n%p==0){n/=p;e++;}
        int sz=res.size(); ll pk=1,ph=1;
        for(int k=1;k<=e;k++){ pk*=p; ph=(k==1)?(p-1):ph*p;
            for(int i=0;i<sz;i++) res.push_back({res[i].first*pk,res[i].second*ph}); }
    }
    if(n>1){ int sz=res.size(); for(int i=0;i<sz;i++) res.push_back({res[i].first*n,res[i].second*(n-1)}); }
    return res;
}
int main(){
    lo[0]=1; for(int i=1;i<(1<<B);i++) lo[i]=lo[i-1]*2%MOD;
    ll step=lo[(1<<B)-1]*2%MOD; hi[0]=1; for(int i=1;i<(1<<B);i++) hi[i]=hi[i-1]*step%MOD;
    int P; scanf("%d",&P);
    while(P--){
        int K; ll n,m; scanf("%d %lld %lld",&K,&n,&m);
        auto dn=divphi(n), dm=divphi(m);
        ll sum=0;
        for(auto&[d,pd]:dn){
            ll nd=n/d;
            for(auto&[e,pe]:dm){
                ll g=std::gcd(d,e);
                ll ex=(nd*((m/e)*g))%(MOD-1);
                ll v=lo[ex&((1<<B)-1)]*hi[ex>>B]%MOD;
                sum=(sum+(pd%MOD)*(pe%MOD)%MOD*v)%MOD;
            }
        }
        ll ans=sum*pw(n%MOD*(m%MOD)%MOD,MOD-2)%MOD;
        printf("%d %lld\n",K,ans);
    }
}
