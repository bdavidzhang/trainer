#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n,s,k; scanf("%lld %lld %lld",&n,&s,&k);
    vector<ll> x(n); for(auto&v:x) scanf("%lld",&v);
    sort(x.begin(),x.end());
    // f(l) = min(l+a, b) on l in [s,hi]: best prefix sum when the current platform has length l
    const ll INF=LLONG_MAX/4;
    ll a=0,b=INF,hi=k;
    for(int i=1;i<n;i++){
        ll D=2*(x[i]-x[i-1]);
        if(D<2*s){ puts("-1"); return 0; }
        ll nhi=min(k,D-s);
        ll na=min(hi+a,b), nb=D+a;
        a=na;b=nb;hi=nhi;
    }
    printf("%lld\n",min(hi+a,b));
}
