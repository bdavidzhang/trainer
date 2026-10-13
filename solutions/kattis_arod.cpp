#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int mx,my; cin>>mx>>my; if(mx>my) swap(mx,my);
    ll N=(ll)(mx+1)*(my+1);
    // cx[a][d+mx]
    vector<vector<ll>> cx(mx+1,vector<ll>(2*mx+1,0)), cy(my+1,vector<ll>(2*my+1,0)), PY(my+1,vector<ll>(2*my+2,0));
    for(int a=0;a<=mx;a++) for(int d=-mx;d<=mx;d++){ int lo=max(0,-d),hi=min(mx-a,mx-d); cx[a][d+mx]=hi>=lo?hi-lo+1:0; }
    for(int b=0;b<=my;b++){ for(int d=-my;d<=my;d++){ int lo=max(0,-d),hi=min(my-b,my-d); cy[b][d+my]=hi>=lo?hi-lo+1:0; }
        // PY[b][k+my+1] = sum d<=k
        PY[b][0]=0; for(int d=-my;d<=my;d++) PY[b][d+my+1]=PY[b][d+my]+cy[b][d+my]; }
    ll S=0,S0=0; ll TY=(ll)(my+1)*(my+1);
    for(int a=0;a<=mx;a++) for(int b=0;b<=my;b++){
        if(!a&&!b) continue;
        ll neg=0,zero=0;
        const ll* cxa=cx[a].data(); const ll* pyb=PY[b].data(); const ll* cyb=cy[b].data();
        for(int d=-(mx-a);d<=mx;d++){
            ll c=cxa[d+mx]; int val=-a*d;
            if(b==0){ if(val>0) neg+=c*TY; else if(val==0) zero+=c*TY; }
            else{
                int v1=val-1; int k=v1>=0? v1/b : -((-v1+b-1)/b);
                if(k>my)k=my; if(k<-my-1)k=-my-1;
                neg+=c*pyb[k+my+1];
                if(val%b==0){ int dy=val/b; if(dy>=-my&&dy<=my) zero+=c*cyb[dy+my]; }
            }
        }
        zero-=cx[a][mx]*cy[b][my];
        ll mult=(a?2:1)*(b?2:1);
        S+=mult*neg; S0+=mult*zero;
    }
    ll D=0;
    for(int dx=0;dx<=mx;dx++) for(int dy=0;dy<=my;dy++){ if(!dx&&!dy)continue; int g=std::gcd(dx,dy);
        D+=(ll)(g-1)*(mx+1-dx)*(my+1-dy)*((dx&&dy)?2:1); }
    ll R=S0/2, O=S/2-D; ll tot=N*(N-1)*(N-2)/6;
    printf("%lld\n%lld\n%lld\n%lld\n",tot-R-O-D,R,O,D);
}
