#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;
// ---------- double-double arithmetic (portable ~106-bit precision) ----------
struct dd{ double hi,lo; };
static inline dd two_sum(double a,double b){ double s=a+b; double bb=s-a; double e=(a-(s-bb))+(b-bb); return {s,e}; }
static inline dd quick(double a,double b){ double s=a+b; return {s,b-(s-a)}; }
static inline dd add(dd a,dd b){ dd s=two_sum(a.hi,b.hi); dd t=two_sum(a.lo,b.lo); s.lo+=t.hi; s=quick(s.hi,s.lo); s.lo+=t.lo; return quick(s.hi,s.lo); }
static inline dd neg(dd a){ return {-a.hi,-a.lo}; }
static inline dd sub(dd a,dd b){ return add(a,neg(b)); }
static inline dd mulD(dd a,double b){ double p=a.hi*b; double e=fma(a.hi,b,-p); e+=a.lo*b; return quick(p,e); }
static inline bool lessdd(dd a,dd b){ return a.hi<b.hi || (a.hi==b.hi && a.lo<b.lo); }
static inline bool leqdd(dd a,dd b){ return !lessdd(b,a); }
static dd sqrtInt(ll x){ // x >= 0, < 9.2e18
    if(x==0) return {0,0};
    double xh=(double)x; double xl=(double)(x-(ll)xh);
    double s=sqrt(xh);
    double p=s*s, e=fma(s,s,-p);
    double r=((xh-p)-e)+xl;
    return quick(s, r/(2*s));
}
// ---------- kd-tree ----------
int n; vector<ll> X,Y; vector<int> ord;
struct Node{ double x0,x1,y0,y1; int l,r; int lc,rc; };
vector<Node> nd;
static int build(int l,int r){
    int id=nd.size(); nd.push_back(Node());
    double x0=1e18,x1=-1e18,y0=1e18,y1=-1e18;
    for(int i=l;i<r;i++){ int p=ord[i]; x0=min(x0,(double)X[p]); x1=max(x1,(double)X[p]); y0=min(y0,(double)Y[p]); y1=max(y1,(double)Y[p]); }
    nd[id].x0=x0;nd[id].x1=x1;nd[id].y0=y0;nd[id].y1=y1;nd[id].l=l;nd[id].r=r;nd[id].lc=nd[id].rc=-1;
    if(r-l>8){
        int mid=(l+r)/2;
        if(x1-x0>=y1-y0) nth_element(ord.begin()+l,ord.begin()+mid,ord.begin()+r,[&](int a,int b){return X[a]<X[b];});
        else nth_element(ord.begin()+l,ord.begin()+mid,ord.begin()+r,[&](int a,int b){return Y[a]<Y[b];});
        int a=build(l,mid); int b=build(mid,r);
        nd[id].lc=a; nd[id].rc=b;
    }
    return id;
}
// query state
ll qpx,qpy,qux,quy; dd qr; double qrUp2, qrLo2, qrHi;
int bestIdx,bestCls; ll bwx,bwy,bd2;
const double EPSC=1e6;
static inline bool reach(ll d2){
    double d=(double)d2;
    if(d>qrUp2) return false;
    if(d<qrLo2) return true;
    return leqdd(sqrtInt(d2),qr);
}
static inline void consider(int p){
    ll wx=X[p]-qpx, wy=Y[p]-qpy;
    if(wx==0&&wy==0) return;
    lll cr=(lll)qux*wy-(lll)quy*wx;
    int cls;
    if(cr>0) cls=1; else if(cr<0) cls=3; else {
        lll dt=(lll)qux*wx+(lll)quy*wy;
        if(dt>0) return; // straight ahead: out of reach by construction
        cls=2;
    }
    ll d2=wx*wx+wy*wy;
    if(bestIdx>=0){
        if(cls>bestCls) return;
        if(cls==bestCls){
            lll c2=(lll)wx*bwy-(lll)wy*bwx; // >0: w is clockwise-before best => smaller angle
            if(c2<0) return;
            if(c2==0 && d2<=bd2) return;
        }
    }
    if(!reach(d2)) return;
    bestIdx=p; bestCls=cls; bwx=wx; bwy=wy; bd2=d2;
}
static inline double boxDist2(const Node&nd_){
    double dx=0,dy=0; double px=(double)qpx, py=(double)qpy;
    if(px<nd_.x0) dx=nd_.x0-px; else if(px>nd_.x1) dx=px-nd_.x1;
    if(py<nd_.y0) dy=nd_.y0-py; else if(py>nd_.y1) dy=py-nd_.y1;
    return dx*dx+dy*dy;
}
static void query(int id){
    const Node&N_=nd[id];
    if(boxDist2(N_)>qrUp2) return;
    if(bestIdx>=0){
        double cx[4]={N_.x0-(double)qpx,N_.x1-(double)qpx,N_.x0-(double)qpx,N_.x1-(double)qpx};
        double cy[4]={N_.y0-(double)qpy,N_.y0-(double)qpy,N_.y1-(double)qpy,N_.y1-(double)qpy};
        double ux=(double)qux,uy=(double)quy,bx=(double)bwx,by=(double)bwy;
        bool allRight=true, allBeyond=true;
        for(int k=0;k<4;k++){
            double cu=ux*cy[k]-uy*cx[k];
            double cb=bx*cy[k]-by*cx[k];
            if(!(cu<-EPSC)) allRight=false;
            if(!(cb>EPSC)) allBeyond=false;
        }
        if(bestCls==1){ if(allRight||allBeyond) return; }
        else if(bestCls==2){ if(allRight) return; }
        else { if(allRight&&allBeyond) return; }
    }
    if(N_.lc<0){
        for(int i=N_.l;i<N_.r;i++) consider(ord[i]);
        return;
    }
    int a=N_.lc,b=N_.rc;
    if(boxDist2(nd[a])>boxDist2(nd[b])) swap(a,b);
    query(a); query(b);
}
int main(){
    ll d;
    if(scanf("%d %lld",&n,&d)!=2) return 0;
    X.resize(n);Y.resize(n);ord.resize(n);
    for(int i=0;i<n;i++){ scanf("%lld %lld",&X[i],&Y[i]); ord[i]=i; }
    nd.reserve(2*n/4+16);
    int root=build(0,n);
    dd r={(double)d,0}; dd S={0,0};
    int cur=-1; qpx=0;qpy=0;qux=1;quy=0;
    vector<int> lastPred(n,-2), lastEpoch(n,-1); vector<dd> lastS(n);
    int epoch=0;
    while(true){
        qr=r; qrHi=r.hi;
        double up=qrHi+1e-3, lo=qrHi-1e-3;
        qrUp2=up*up*(1+1e-12); qrLo2= lo>0? lo*lo*(1-1e-12) : -1;
        bestIdx=-1;
        query(root);
        if(bestIdx<0) break;
        int q=bestIdx;
        dd dist=sqrtInt(bd2);
        r=sub(r,dist); S=add(S,dist);
        qux=bwx; quy=bwy; qpx=X[q]; qpy=Y[q];
        int pred=cur; cur=q;
        if(lastEpoch[cur]==epoch && lastPred[cur]==pred){
            // same directed edge traversed again: the loop of length p repeats while the rope lasts
            dd p=sub(S,lastS[cur]);
            if(leqdd(p,r) && p.hi>0){
                double k=floor(r.hi/p.hi);
                dd rem=sub(r,mulD(p,k));
                while(rem.hi<0 || (rem.hi==0&&rem.lo<0)) rem=add(rem,p);
                while(leqdd(p,rem)) rem=sub(rem,p);
                r=rem; epoch++;
            }
        }
        lastEpoch[cur]=epoch; lastPred[cur]=pred; lastS[cur]=S;
    }
    printf("%d\n",cur<0?-1:cur+1);
}
