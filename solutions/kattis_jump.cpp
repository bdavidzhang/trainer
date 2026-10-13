#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static ll ext(ll a, ll b, ll &x, ll &y){ if(!b){ x=1; y=0; return a; } ll x1,y1; ll g=ext(b,a%b,x1,y1); x=y1; y=x1-(a/b)*y1; return g; }
int main(){
    ll N,E; scanf("%lld %lld",&N,&E);
    // kk[r]: starting on a beat with energy e = r (mod N), the first jump index k that lands on a beat:
    // k*e - k(k-1)/2 = 0 (mod N). Periodic in k with period 2N.
    vector<int> kk(N,0); ll assigned=0;
    for(ll k=1;k<=2*N && assigned<N;k++){
        ll c=(k*(k-1)/2)%N;
        ll g=std::gcd(k,N);
        if(c%g) continue;
        ll M=N/g, a=(k/g)%M, x,y;
        ll r0=0;
        if(M>1){ ext(a,M,x,y); x%=M; if(x<0) x+=M; r0=(ll)((__int128)(c/g)%M*x%M); }
        for(ll r=r0;r<N;r+=M) if(!kk[r]){ kk[r]=(int)k; assigned++; }
    }
    __int128 t=0; ll e=E;
    while(true){
        ll k=kk[e%N];
        if(k==0||k>e){ t+=(__int128)e*(e+1)/2; break; }
        if(k<=2){ puts("infinity"); return 0; }
        t+=(__int128)k*e-(__int128)k*(k-1)/2;
        e=e-k+2;
    }
    string s; if(t==0) s="0";
    while(t>0){ s+=char('0'+(int)(t%10)); t/=10; }
    reverse(s.begin(),s.end());
    puts(s.c_str());
}
