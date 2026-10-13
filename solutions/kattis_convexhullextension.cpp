#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;
static LL fdiv(LL a, LL b){ // floor, b>0
    LL q=a/b; if(a%b!=0 && (a<0)) q--; return q;
}
// sum_{i=0}^{n-1} floor((a*i+b)/m), m>0
static LL fsum(LL n, LL m, LL a, LL b){
    LL ans=0;
    while(true){
        if(n<=0) return ans;
        if(a<0||a>=m){ LL q=fdiv(a,m); ans+=q*(n*(n-1)/2); a-=q*m; }
        if(b<0||b>=m){ LL q=fdiv(b,m); ans+=q*n; b-=q*m; }
        LL ymax=a*n+b;
        if(ymax<m) return ans;
        LL nn=ymax/m, nb=ymax%m;
        n=nn; b=nb; swap(m,a);
    }
}
struct C{ ll a,b,c; }; // a x + b y + c >= 1
struct Fr{ LL n,d; }; // d>0
static bool lessFr(const Fr&p,const Fr&q){ return p.n*q.d<q.n*p.d; }
static LL countTri(C cs[3]){
    Fr xs[3];
    for(int m=0;m<3;m++){
        int j=(m+1)%3,k=(m+2)%3;
        LL ej=1-cs[j].c, ek=1-cs[k].c;
        LL D=(LL)cs[j].a*cs[k].b-(LL)cs[k].a*cs[j].b;
        LL xn=ej*cs[k].b-ek*cs[j].b, yn=cs[j].a*ek-cs[k].a*ej;
        LL val=cs[m].a*xn+cs[m].b*yn+(LL)(cs[m].c-1)*D;
        if(D<0){ val=-val; xn=-xn; D=-D; }
        if(val<0) return 0;
        xs[m]={xn,D};
    }
    sort(xs,xs+3,lessFr);
    LL XL=-fdiv(-xs[0].n,xs[0].d), XM=fdiv(xs[1].n,xs[1].d), XR=fdiv(xs[2].n,xs[2].d);
    LL total=0;
    auto piece=[&](LL l,LL r){
        if(l>r)return;
        int lo=-1,up=-1;
        // value of line j at x: (1-c-a x)/b
        auto cmp=[&](int p,int q,LL x)->int{ // compare line p vs q values at x: sign(p-q)
            LL np=1-cs[p].c-(LL)cs[p].a*x, dp=cs[p].b, nq=1-cs[q].c-(LL)cs[q].a*x, dq=cs[q].b;
            if(dp<0){np=-np;dp=-dp;} if(dq<0){nq=-nq;dq=-dq;}
            LL v=np*dq-nq*dp; return v>0?1:v<0?-1:0;
        };
        for(int j=0;j<3;j++){
            if(cs[j].b>0){
                if(lo<0)lo=j; else { int c1=cmp(j,lo,l); if(c1>0||(c1==0&&cmp(j,lo,r)>0))lo=j; }
            } else if(cs[j].b<0){
                if(up<0)up=j; else { int c1=cmp(j,up,l); if(c1<0||(c1==0&&cmp(j,up,r)<0))up=j; }
            }
        }
        if(lo<0||up<0)return; // should not happen
        LL n=r-l+1;
        // sum floor((a_u x + c_u -1)/(-b_u)) + floor((a_l x + c_l -1)/b_l) + 1
        total+=fsum(n,-cs[up].b,cs[up].a,(LL)cs[up].a*l+cs[up].c-1);
        total+=fsum(n,cs[lo].b,cs[lo].a,(LL)cs[lo].a*l+cs[lo].c-1);
        total+=n;
    };
    piece(XL,min(XM,XR));
    piece(max(XM+1,XL),XR);
    return total;
}
int main(){
    int n; scanf("%d",&n); vector<ll> x(n),y(n); for(int i=0;i<n;i++)scanf("%lld %lld",&x[i],&y[i]);
    LL total=0; bool inf=false;
    auto mk=[&](ll dx,ll dy,ll ox,ll oy,int sgn){ // sgn*cross(d, X-O) >= 1
        C c; c.a=-dy*sgn; c.b=dx*sgn; c.c=(dy*ox-dx*oy)*sgn; return c; };
    for(int i=0;i<n&&!inf;i++){
        int pr=(i+n-1)%n, q=(i+1)%n, nx=(i+2)%n;
        ll d1x=x[i]-x[pr], d1y=y[i]-y[pr], d2x=x[nx]-x[q], d2y=y[nx]-y[q];
        ll ex=x[q]-x[i], ey=y[q]-y[i];
        ll cr=d1x*d2y-d1y*d2x;
        if(cr<0){ inf=true; break; }
        if(cr==0){
            ll g=std::gcd(llabs(d1x),llabs(d1y));
            ll w=(d1x/g)*ey-(d1y/g)*ex;
            if(llabs(w)>=2){ inf=true; break; }
            continue;
        }
        C cs[3]={ mk(ex,ey,x[i],y[i],-1), mk(d1x,d1y,x[pr],y[pr],1), mk(d2x,d2y,x[q],y[q],1) };
        total+=countTri(cs);
    }
    if(inf)puts("infinitely many"); else printf("%lld\n",(ll)total);
}
