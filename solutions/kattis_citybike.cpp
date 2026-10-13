#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n; ll d,c; vector<ll> a;
// 0 ok, -1 L too low (truck overflows), +1 L too high (truck runs out)
static int chk(ll L,ll D){
    ll lo=0,hi=c;
    for(int i=0;i<n;i++){
        lo+=a[i]-(L+D); hi+=a[i]-L;
        if(hi<0) return 1;
        if(lo>c) return -1;
        if(lo<0) lo=0;
        if(hi>c) hi=c;
    }
    return 0;
}
static bool feas(ll D){
    ll lo=0,hi=d-D;
    while(lo<=hi){ ll mid=(lo+hi)/2; int v=chk(mid,D); if(v==0) return true; if(v<0) lo=mid+1; else hi=mid-1; }
    return false;
}
int main(){
    scanf("%d %lld %lld",&n,&d,&c);
    a.resize(n); for(auto&x:a) scanf("%lld",&x);
    ll lo=0,hi=d;
    while(lo<hi){ ll mid=(lo+hi)/2; if(feas(mid)) hi=mid; else lo=mid+1; }
    printf("%lld\n",lo);
}
