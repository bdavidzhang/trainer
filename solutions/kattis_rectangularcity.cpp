#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1000000007;
ll pw(ll b,ll e){ll r=1;b%=MOD;while(e){if(e&1)r=r*b%MOD;b=b*b%MOD;e>>=1;}return r;}
// F[h] = number of N-tuples of intervals in [1..R] whose intersection has length >= h, h=1..R ; F[R+1]=0
vector<ll> calc(int R,ll N){
    vector<ll> p(R+2); for(int i=0;i<=R+1;i++) p[i]=pw(i,N);
    vector<ll> G(R+3,0);
    for(int h=1;h<=R;h++){
        // l from 1..R-h+1 : p[l]*p[R-(l+h-1)+1]
        unsigned long long s=0; 
        for(int l=1;l+h-1<=R;l++){ s+=(unsigned long long)p[l]*p[R-l-h+2]%MOD; }
        G[h]=s%MOD;
    }
    vector<ll> F(R+2,0);
    for(int h=1;h<=R;h++) F[h]=(G[h]-G[h+1]+MOD)%MOD;
    return F;
}
int main(){
    ll N,R,C,K; scanf("%lld %lld %lld %lld",&N,&R,&C,&K);
    vector<ll> FR=calc(R,N), FC=calc(C,N);
    ll ans=0;
    for(ll h=1;h<=R;h++){
        ll w=(K+h-1)/h; if(w>C) continue;
        ll fr=(FR[h]-FR[h+1]+MOD)%MOD;
        ans=(ans+fr*FC[w])%MOD;
    }
    printf("%lld\n",ans);
}
