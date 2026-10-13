#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
struct V{ld x,y,z;};
V operator-(V a,V b){return {a.x-b.x,a.y-b.y,a.z-b.z};}
V operator+(V a,V b){return {a.x+b.x,a.y+b.y,a.z+b.z};}
V operator*(V a,ld k){return {a.x*k,a.y*k,a.z*k};}
ld dot(V a,V b){return a.x*b.x+a.y*b.y+a.z*b.z;}
ld clampv(ld v){return v<0?0:(v>1?1:v);}
// squared distance between segments p1q1 and p2q2
ld segseg(V p1,V q1,V p2,V q2){
    V d1=q1-p1,d2=q2-p2,r=p1-p2;
    ld a=dot(d1,d1),e=dot(d2,d2),f=dot(d2,r),s,t;
    const ld EPS=1e-18L;
    if(a<=EPS&&e<=EPS){return dot(r,r);}
    if(a<=EPS){s=0;t=clampv(f/e);}
    else{
        ld c=dot(d1,r);
        if(e<=EPS){t=0;s=clampv(-c/a);}
        else{
            ld b=dot(d1,d2),den=a*e-b*b;
            if(den>1e-12L*a*e) s=clampv((b*f-c*e)/den); else s=0;
            t=(b*s+f)/e;
            if(t<0){t=0;s=clampv(-c/a);}
            else if(t>1){t=1;s=clampv((b-c)/a);}
        }
    }
    V c1=p1+d1*s,c2=p2+d2*t,w=c1-c2;
    return dot(w,w);
}
ld ptseg(V p,V a,V b){V d=b-a;ld l=dot(d,d);ld t=l>0?clampv(dot(p-a,d)/l):0;V w=p-(a+d*t);return dot(w,w);}
int main(){
    V s,b;int n;
    auto rd=[&](V&v){double x,y,z;scanf("%lf %lf %lf",&x,&y,&z);v={x,y,z};};
    rd(s);rd(b);scanf("%d",&n);
    bool bad=false;
    for(int i=0;i<n;i++){
        V p,d;int m;rd(p);rd(d);scanf("%d",&m);
        ld R2=0;
        for(int j=0;j<m;j++){V c;rd(c);V w=c-p;R2=max(R2,dot(w,w));}
        ld dl=sqrtl(dot(d,d));
        V e=p+d*(3e7L/dl);
        ld D=segseg(s,b,p,e);
        // safety: also endpoints
        D=min(D,min(min(ptseg(s,p,e),ptseg(b,p,e)),min(ptseg(p,s,b),ptseg(e,s,b))));
        if(sqrtl(D)<sqrtl(R2))bad=true;
    }
    puts(bad?"Surrender":"Go");
}
