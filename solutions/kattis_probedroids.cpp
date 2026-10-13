#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N,M; // y in 0..N, x in 0..M
// sum_{i=0}^{n-1} floor((a*i+b)/m)
ll floor_sum(ll n,ll m,ll a,ll b){
    ll ans=0;
    while(true){
        if(a>=m){ans+=(n-1)*n/2*(a/m);a%=m;}
        if(b>=m){ans+=n*(b/m);b%=m;}
        ll y=a*n+b; if(y<m) break;
        n=y/m; b=y%m; swap(m,a);
    }
    return ans;
}
// number of droids with x>=1 and y/x <= p/q   (p>=1,q>=1)
ll cnt(ll p,ll q){
    ll x0=min(M,((N+1)*q-1)/p);
    return floor_sum(x0+1,q,p,0)+(M-x0)*N+M;
}
int main(){
    ll n,m;int Q; scanf("%lld %lld %d",&n,&m,&Q); N=n-1;M=m-1;
    ll total=(N+1)*(M+1)-1;
    while(Q--){
        ll i; scanf("%lld",&i);
        if(i<=M){printf("1 %lld\n",i+1);continue;}
        if(i>total-N){printf("%lld 1\n",i-(total-N)+1);continue;}
        // Stern-Brocot: lo false, hi true
        ll pl=0,ql=1,ph=1,qh=0;
        auto inb=[&](ll p,ll q){return p<=N&&q<=M;};
        while(true){
            ll pm=pl+ph,qm=ql+qh;
            if(!inb(pm,qm)) break;
            if(cnt(pm,qm)>=i){
                // move hi towards lo: hi = hi + t*lo, largest t with in-bounds and true
                ll t=1;
                auto good=[&](ll t){ll p=ph+t*pl,q=qh+t*ql; return inb(p,q)&&cnt(p,q)>=i;};
                while(good(t*2)) t*=2;
                ll a=t,b=t*2; // good(a), !good(b)
                while(b-a>1){ll c=(a+b)/2; if(good(c))a=c; else b=c;}
                ph+=a*pl; qh+=a*ql;
            }else{
                ll t=1;
                auto good=[&](ll t){ll p=pl+t*ph,q=ql+t*qh; return inb(p,q)&&cnt(p,q)<i;};
                while(good(t*2)) t*=2;
                ll a=t,b=t*2;
                while(b-a>1){ll c=(a+b)/2; if(good(c))a=c; else b=c;}
                pl+=a*ph; ql+=a*qh;
            }
        }
        ll onray=min(M/qh,N/ph);
        ll before=cnt(ph,qh)-onray;
        ll t=i-before;
        printf("%lld %lld\n",t*ph+1,t*qh+1);
    }
}
