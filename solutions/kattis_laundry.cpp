#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int t; scanf("%d",&t);
    while(t--){
        ll k,c[7]; scanf("%lld",&k); for(auto&x:c)scanf("%lld",&x);
        auto ce=[&](ll x){return (x+k-1)/k;};
        ll la=ce(c[0]),lb=ce(c[1]),lc=ce(c[2]);
        ll pab=ce(c[0]+c[1]+c[3]),pbc=ce(c[1]+c[2]+c[4]),pac=ce(c[0]+c[2]+c[5]);
        ll T=ce(c[0]+c[1]+c[2]+c[3]+c[4]+c[5]+c[6]);
        ll S=max({T,la+lb+lc,pab+lc,pbc+la,pac+lb,(pab+pbc+pac+1)/2});
        printf("%lld\n",S);
    }
}
