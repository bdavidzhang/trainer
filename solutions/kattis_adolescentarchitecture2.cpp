#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef unsigned __int128 u128;
// types: 0 circle (radius), 1 square (side), 2 triangle (side)
// does (t1,a) fit strictly inside (t2,b)?  all predicates exact in integers
static bool fits(int t1,ll a_,int t2,ll b_){
    u128 a=a_,b=b_;
    if(t1==t2) return a<b;
    if(t1==2&&t2==0) return a*a<3*b*b;          // triangle in circle: a/sqrt3 < r
    if(t1==1&&t2==0) return a*a<2*b*b;          // square in circle
    if(t1==0&&t2==1) return 2*a<b;              // circle in square
    if(t1==0&&t2==2) return 12*a*a<b*b;         // circle in triangle: r < a/(2 sqrt3)
    if(t1==2&&t2==1){                           // triangle in square: a < b*(sqrt6-sqrt2)
        if(a*a>=8*b*b) return false;
        u128 d=8*b*b-a*a;                       // need 4*sqrt3*b^2 < d
        return 48*b*b*b*b<d*d;
    }
    // square a in triangle b: a < b*(2 sqrt3 - 3)
    return (a+3*b)*(a+3*b)<12*b*b;
}
static ll maxfit(int t1,int t2,ll b){ // largest a with (t1,a) inside (t2,b), 0 if none
    ll lo=0,hi=2000000000LL;
    while(lo<hi){ ll m=(lo+hi+1)/2; if(fits(t1,m,t2,b)) lo=m; else hi=m-1; }
    return lo;
}
#ifndef LIM
#define LIM 400
#endif
static ll memo[3][LIM+1]; static bool have[3][LIM+1];
static ll G(int t,ll a){
    if(a<=0) return -1;
    if(a>LIM) return maxfit(2,t,a);   // long chain of triangles dominates for large sizes
    if(have[t][a]) return memo[t][a];
    ll best=-1;
    for(int u=0;u<3;u++) best=max(best,G(u,maxfit(u,t,a)));
    have[t][a]=true; return memo[t][a]=best+1;
}
int main(){
#ifdef VERIFY
    for(int t=0;t<3;t++) for(ll a=1;a<=LIM;a++) if(G(t,a)!=maxfit(2,t,a)) printf("mismatch t=%d a=%lld g=%lld f=%lld\n",t,a,G(t,a),maxfit(2,t,a));
    return 0;
#endif
    int n; cin>>n; vector<int> T(n); vector<ll> A(n),g(n); ll S=0;
    for(int i=0;i<n;i++){
        string s; cin>>s>>A[i]; T[i]=s=="circle"?0:s=="square"?1:2;
        g[i]=G(T[i],A[i]); S^=g[i];
    }
    const ll HI[3]={1000000000LL,1420000000LL,1740000000LL};
    ll ans=0;
    for(int i=0;i<n;i++){
        ll target=S^g[i];
        if(target>=g[i]) continue;
        for(int u=0;u<3;u++){
            ll lo=1,hi=HI[u];   // smallest a with G(u,a)>=target (G strictly increasing in a)
            while(lo<hi){ ll m=(lo+hi)/2; if(G(u,m)>=target) hi=m; else lo=m+1; }
            if(G(u,lo)==target && fits(u,lo,T[i],A[i])) ans++;
        }
    }
    cout<<ans<<"\n";
}
