#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef __int128 LL;
// WLOG torque T>0: people only move left. y_i = shift >= 0, y_i - y_{i-1} <= p_i - p_{i-1}.
// f(C) = max torque removed with total movement C is concave; Lagrangian max sum (w_i-lam) y_i has
// vertex solutions = partition into blocks, each collapsing onto its leftmost member -> CHT dp.
// lam = N / 2^32 exactly, dp in __int128, binary search N.
int n; vector<ll> p,w,P,W,WP; const ll D=1LL<<32;
vector<LL> Cs,CP,dp; vector<int> from_;
struct Line{LL m,b;int id;};
ll resC,resF;
void eval(ll N){
    for(int i=1;i<=n;i++){LL c=(LL)w[i]*D-N;Cs[i]=Cs[i-1]+c;CP[i]=CP[i-1]+c*p[i];}
    vector<Line> h;h.reserve(n);
    dp[0]=0;
    for(int r=1;r<=n;r++){
        Line L{-(LL)p[r],dp[r-1]-CP[r-1]+(LL)p[r]*Cs[r-1],r};
        while(h.size()>=2){Line&a=h[h.size()-2];Line&b=h.back();
            // slopes decreasing; b useless if intersection(a,L) is at x >= ... for max hull with decreasing slopes
            // a best for large... with decreasing slopes, later lines win for small x? no: larger slope wins for large x.
            // lines a (largest slope), b, L (smallest). b needed iff x(b,L) < x(a,b), where
            // x(a,b)=(b.b-a.b)/(a.m-b.m), x(b,L)=(L.b-b.b)/(b.m-L.m).
            if((L.b-b.b)*(a.m-b.m)>=(b.b-a.b)*(b.m-L.m))h.pop_back();else break;}
        h.push_back(L);
        // query x=Cs[r]: hull from h[0] (largest slope, best for large x) to h.back() (best for small x)
        LL x=Cs[r];int lo=0,hi=(int)h.size()-1;
        while(lo<hi){int mid=(lo+hi)/2;
            if(h[mid].m*x+h[mid].b>=h[mid+1].m*x+h[mid+1].b)hi=mid;else lo=mid+1;}
        dp[r]=CP[r]+h[lo].m*x+h[lo].b;from_[r]=h[lo].id;
    }
    resC=0;resF=0;int r=n;
    while(r>0){int l=from_[r];
        resC+=P[r]-P[l-1]-p[l]*(r-l+1);
        resF+=WP[r]-WP[l-1]-p[l]*(W[r]-W[l-1]);
        r=l-1;}
}
int main(){scanf("%d",&n);p.assign(n+1,0);w.assign(n+1,0);
    for(int i=1;i<=n;i++)scanf("%lld %lld",&p[i],&w[i]);
    ll T=0;for(int i=1;i<=n;i++)T+=p[i]*w[i];
    if(T==0){puts("0.000000");return 0;}
    if(T<0){reverse(p.begin()+1,p.end());reverse(w.begin()+1,w.end());for(int i=1;i<=n;i++)p[i]=-p[i];T=-T;}
    P.assign(n+1,0);W.assign(n+1,0);WP.assign(n+1,0);Cs.assign(n+1,0);CP.assign(n+1,0);dp.assign(n+1,0);from_.assign(n+1,0);
    ll Nlo=0,Nhi=0;
    for(int i=1;i<=n;i++){P[i]=P[i-1]+p[i];W[i]=W[i-1]+w[i];WP[i]=WP[i-1]+p[i]*w[i];
        LL num=(LL)W[i]*D;ll c=(ll)((num+i-1)/i);Nlo=max(Nlo,c);Nhi=max(Nhi,w[i]*D);}
    // F(N) nonincreasing in N; find smallest N in [Nlo,Nhi] with F(N)<=T
    ll lo=Nlo,hi=Nhi;
    while(lo<hi){ll mid=lo+(hi-lo)/2;eval(mid);if(resF<=T)hi=mid;else lo=mid+1;}
    eval(lo);
    long double ans=(long double)resC+(long double)(T-resF)*(long double)D/(long double)lo;
    printf("%.7Lf\n",ans);
}
