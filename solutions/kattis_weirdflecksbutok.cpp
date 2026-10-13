#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
struct P{ld x,y;};
struct C{ld x,y,r;};
static bool in(const C&c,const P&p){ld dx=p.x-c.x,dy=p.y-c.y; return sqrtl(dx*dx+dy*dy)<=c.r+1e-10L;}
static C two(const P&a,const P&b){ld x=(a.x+b.x)/2,y=(a.y+b.y)/2; return {x,y,hypotl(a.x-b.x,a.y-b.y)/2};}
static C three(const P&a,const P&b,const P&c){
    ld bx=b.x-a.x,by=b.y-a.y,cx=c.x-a.x,cy=c.y-a.y;
    ld d=2*(bx*cy-by*cx);
    if(fabsl(d)<1e-18L){ // collinear: widest pair
        C r=two(a,b); C r2=two(a,c); C r3=two(b,c);
        if(r2.r>r.r) r=r2; if(r3.r>r.r) r=r3; return r;
    }
    ld ux=(cy*(bx*bx+by*by)-by*(cx*cx+cy*cy))/d, uy=(bx*(cx*cx+cy*cy)-cx*(bx*bx+by*by))/d;
    return {a.x+ux,a.y+uy,hypotl(ux,uy)};
}
static ld mec(vector<P> p){
    mt19937 rng(712367);
    shuffle(p.begin(),p.end(),rng);
    int n=p.size(); C c={p[0].x,p[0].y,0};
    for(int i=1;i<n;i++) if(!in(c,p[i])){
        c={p[i].x,p[i].y,0};
        for(int j=0;j<i;j++) if(!in(c,p[j])){
            c=two(p[i],p[j]);
            for(int k=0;k<j;k++) if(!in(c,p[k])) c=three(p[i],p[j],p[k]);
        }
    }
    return c.r;
}
int main(){
    int n; scanf("%d",&n);
    vector<array<double,3>> a(n);
    for(auto&v:a) scanf("%lf %lf %lf",&v[0],&v[1],&v[2]);
    ld best=1e18;
    for(int s=0;s<3;s++){
        vector<P> p(n); for(int i=0;i<n;i++) p[i]={a[i][s],a[i][(s+1)%3]};
        best=min(best,mec(p));
    }
    printf("%.10Lf\n",2*best);
}
