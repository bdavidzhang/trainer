#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef unsigned long long ull;
int main(){
    ll p,q; cin>>p>>q;
    for(ll r=1;r<=1000000;r++){
        // p n^2 - (p+2qr) n + 2 q r^2 = 0, n=r+g>=2r
        ll B=p+2*q*r; ll D=B*B-8*p*q*r*r;
        if(D<0) continue;
        ll s=(ll)sqrtl((long double)D); while(s*s>D)s--; while((s+1)*(s+1)<=D)s++;
        if(s*s!=D) continue;
        ll best=-1;
        for(int sg=-1;sg<=1;sg+=2){
            ll num=B+sg*s; if(num<=0||num%(2*p)) continue;
            ll n=num/(2*p); if(n>=2*r){ if(best<0||n<best) best=n; }
        }
        if(best>0){ printf("%lld %lld\n",r,best-r); return 0; }
    }
    puts("impossible");
}
