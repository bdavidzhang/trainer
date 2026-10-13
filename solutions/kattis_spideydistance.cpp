#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll t,s; scanf("%lld %lld",&t,&s);
    ll num=0,den=0;
    for(ll x=0;x<=s;x++){
        // spidey: 2*max+min <= 2s
        ll y=min(x,2*s-2*x);
        ll y2=(2*s-x)/2; if(y2>x) y=max(y,y2);
        ll mult=x?2:1;
        den+=mult*(2*y+1);
        ll yt=min(y,t-x);
        if(yt>=0) num+=mult*(2*yt+1);
    }
    ll g=std::gcd(num,den); num/=g; den/=g;
    if(den==1) printf("%lld\n",num); else printf("%lld/%lld\n",num,den);
}
