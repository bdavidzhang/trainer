#include <bits/stdc++.h>
using namespace std;
typedef double D;
struct Pt{D x,y;};
static D segDist(D px,D py,Pt a,Pt b){
    D vx=b.x-a.x, vy=b.y-a.y, wx=px-a.x, wy=py-a.y;
    D t=(vx*wx+vy*wy)/(vx*vx+vy*vy); t=max((D)0,min((D)1,t));
    return hypot(px-(a.x+t*vx), py-(a.y+t*vy));
}
static D rayDist(D px,D py,Pt a){ // vertical ray upward from a
    if(py>=a.y) return fabs(px-a.x);
    return hypot(px-a.x,py-a.y);
}
// distance to convex region {a.x<=x<=b.x, y>=line(x)}
static D regDist(D px,D py,Pt a,Pt b){
    if(px>=a.x&&px<=b.x){
        D ly=a.y+(b.y-a.y)*(px-a.x)/(b.x-a.x);
        if(py>=ly) return 0;
    }
    return min(segDist(px,py,a,b), min(rayDist(px,py,a), rayDist(px,py,b)));
}
// visibility envelope to the right of the camera; returns earliest path length or -1
static D solveRight(vector<Pt> ter, D c, D sx, D sy, D r, D dx, D dy){
    int n=ter.size();
    // camera point
    D cy=0; int seg=-1;
    for(int i=0;i+1<n;i++) if(c>=ter[i].x && c<=ter[i+1].x){ seg=i; cy=ter[i].y+(ter[i+1].y-ter[i].y)*(c-ter[i].x)/(ter[i+1].x-ter[i].x); }
    if(seg<0) return -1;
    vector<Pt> pts; pts.push_back({c,cy});
    for(int i=0;i<n;i++) if(ter[i].x>c) pts.push_back(ter[i]);
    vector<Pt> h; h.push_back(pts[0]);
    bool has=false; D s=0;
    for(size_t i=0;i+1<pts.size();i++){
        Pt p=pts[i], q=pts[i+1];
        if(has){
            D rp=cy+s*(p.x-c), rq=cy+s*(q.x-c);
            D e1=p.y-rp, e2=q.y-rq;
            const D E=1e-9;
            if((e1<-E&&e2>E)||(e1>E&&e2<-E)){
                D t=e1/(e1-e2);
                h.push_back({p.x+t*(q.x-p.x), p.y+t*(q.y-p.y)});
            }
            h.push_back({q.x, max(q.y,rq)});
        } else h.push_back(q);
        D sq=(q.y-cy)/(q.x-c);
        if(!has||sq>s){s=sq;has=true;}
    }
    D len=hypot(dx,dy), ux=dx/len, uy=dy/len;
    D best=-1;
    const D LMAX=3e8;
    for(size_t i=0;i+1<h.size();i++){
        Pt a=h[i], b=h[i+1];
        if(b.x-a.x<1e-12) continue;
        auto f=[&](D L){ return regDist(sx+ux*L, sy+uy*L, a, b); };
        D res;
        if(f(0)<r-1e-9) res=0;
        else {
            D lo=0, hi=LMAX;
            for(int it=0;it<200;it++){
                D m1=lo+(hi-lo)/3, m2=hi-(hi-lo)/3;
                if(f(m1)<=f(m2)) hi=m2; else lo=m1;
            }
            D Lm=(lo+hi)/2;
            if(f(Lm)>=r-1e-7) continue;
            lo=0; hi=Lm;
            for(int it=0;it<100;it++){ D m=(lo+hi)/2; if(f(m)<r) hi=m; else lo=m; }
            res=hi;
        }
        if(best<0||res<best) best=res;
    }
    return best;
}
int main(){
    int n; scanf("%d",&n);
    vector<Pt> ter(n+1);
    for(auto& p: ter) scanf("%lf %lf",&p.x,&p.y);
    D c,sx,sy,r,dx,dy,v; scanf("%lf %lf %lf %lf %lf %lf %lf",&c,&sx,&sy,&r,&dx,&dy,&v);
    D a=solveRight(ter,c,sx,sy,r,dx,dy);
    vector<Pt> m(ter.rbegin(),ter.rend()); for(auto& p:m) p.x=-p.x;
    D b=solveRight(m,-c,-sx,sy,r,-dx,dy);
    D best=-1;
    if(a>=0) best=a;
    if(b>=0&&(best<0||b<best)) best=b;
    if(best<0) printf("-1\n"); else printf("%.6f\n",best/v);
}
