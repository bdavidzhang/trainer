#include <bits/stdc++.h>
using namespace std;
typedef double ld;
struct P{ld x,y;};
static inline P operator+(P a,P b){return {a.x+b.x,a.y+b.y};}
static inline P operator-(P a,P b){return {a.x-b.x,a.y-b.y};}
static inline P operator*(P a,ld k){return {a.x*k,a.y*k};}
static inline ld cross(P a,P b){return a.x*b.y-a.y*b.x;}
static inline ld dot(P a,P b){return a.x*b.x+a.y*b.y;}
static inline ld len(P a){return sqrt(a.x*a.x+a.y*a.y);}
int n;
P SA[20],SB[20];
// tour state
int L,K; P Ps,Qt; ld bestTour;
P IA[20],IW[20]; // image of a, image direction (b'-a')
struct T{ld m00,m01,m10,m11,cx,cy;};
static inline P app(const T&t,P p){return {t.m00*p.x+t.m01*p.y+t.cx,t.m10*p.x+t.m11*p.y+t.cy};}
void leaf(const T&t){
    P q=app(t,Qt);P v=q-Ps;ld lv=len(v);
    if(lv>=bestTour)return; // straight unfolded length is a lower bound for this unfolding's real path
    P prev=Ps;ld tot=0;
    for(int m=0;m<K;m++){
        P w=IW[m];ld den=cross(w,v);ld lw=len(w);ld mu;
        P d=Ps-IA[m];
        if(fabs(den)<=1e-11*lw*lv||lv==0)mu=dot(d,w)/(lw*lw);
        else mu=cross(d,v)/den;
        if(!(mu>0))mu=0; if(mu>1)mu=1;
        P x=SA[L+m]+(SB[L+m]-SA[L+m])*mu;
        tot+=len(x-prev);prev=x;
        if(tot>=bestTour)return;
    }
    tot+=len(Qt-prev);
    if(tot<bestTour)bestTour=tot;
}
void dfs(int m,const T&t){
    if(m==K){leaf(t);return;}
    P a=app(t,SA[L+m]),b=app(t,SB[L+m]);
    IA[m]=a;IW[m]=b-a;
    dfs(m+1,t);
    // reflect across line a,b
    P w=b-a;ld l2=dot(w,w);ld ux=w.x,uy=w.y;
    ld s00=2*ux*ux/l2-1,s01=2*ux*uy/l2,s10=s01,s11=2*uy*uy/l2-1;
    T r;
    r.m00=s00*t.m00+s01*t.m10;r.m01=s00*t.m01+s01*t.m11;
    r.m10=s10*t.m00+s11*t.m10;r.m11=s10*t.m01+s11*t.m11;
    ld dx=t.cx-a.x,dy=t.cy-a.y;
    r.cx=a.x+s00*dx+s01*dy;r.cy=a.y+s10*dx+s11*dy;
    dfs(m+1,r);
}
ld tour(P p,int l,int r,P q){ // segments l..r inclusive strictly between
    if(l>r)return len(q-p);
    L=l;K=r-l+1;Ps=p;Qt=q;bestTour=1e300;
    T id={1,0,0,1,0,0};
    dfs(0,id);
    return bestTour;
}
int main(){
    scanf("%d",&n);
    P s,t;scanf("%lf %lf",&s.x,&s.y);
    for(int i=1;i<=n;i++)scanf("%lf %lf %lf %lf",&SA[i].x,&SA[i].y,&SB[i].x,&SB[i].y);
    scanf("%lf %lf",&t.x,&t.y);
    vector<vector<P>> cand(n+2);
    cand[0]={s};cand[n+1]={t};
    auto inter=[&](int i,int j,P&out){
        P a=SA[i],b=SB[i],c=SA[j],d=SB[j];
        ld den=cross(b-a,d-c);
        if(den==0)return false;
        ld u=cross(c-a,d-c)/den,w=cross(c-a,b-a)/den;
        if(u<-1e-12||u>1+1e-12||w<-1e-12||w>1+1e-12)return false;
        u=min((ld)1,max((ld)0,u));
        out=a+(b-a)*u;return true;
    };
    for(int i=1;i<=n;i++){
        cand[i].push_back(SA[i]);cand[i].push_back(SB[i]);
        P x;
        if(i>1&&inter(i,i-1,x))cand[i].push_back(x);
        if(i<n&&inter(i,i+1,x))cand[i].push_back(x);
    }
    vector<vector<ld>> best(n+2);
    best[0]={0};
    for(int i=1;i<=n+1;i++){
        best[i].assign(cand[i].size(),1e300);
        for(size_t c=0;c<cand[i].size();c++)
            for(int j=0;j<i;j++)for(size_t e=0;e<cand[j].size();e++){
                ld v=best[j][e]+tour(cand[j][e],j+1,i-1,cand[i][c]);
                if(v<best[i][c])best[i][c]=v;
            }
    }
    printf("%.9f\n",best[n+1][0]);
}
