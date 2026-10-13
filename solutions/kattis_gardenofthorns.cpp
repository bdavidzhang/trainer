#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
ld R;
// antiderivative of sqrt(R^2-t^2)
ld G(ld t){ if(t>R)t=R; if(t<-R)t=-R; return (t*sqrtl(max((ld)0,R*R-t*t))+R*R*asinl(t/R))/2; }
// integral over t in [lo,hi] (within [-R,R]) of min(c, sqrt(R^2-t^2))
ld F(ld c,ld lo,ld hi){
    if(lo>=hi) return 0;
    if(c>=R) return G(hi)-G(lo);
    ld d=sqrtl(R*R-c*c);
    ld res=0;
    ld l=max(lo,-d), h=min(hi,d);
    if(h>l) res+=c*(h-l);
    if(lo<-d) res+=G(min(hi,-d))-G(lo);
    if(hi>d) res+=G(hi)-G(max(lo,d));
    return res;
}
int main(){int n;int r,w,h;cin>>n>>r>>w>>h;R=r;ld tot=0;
 for(int i=0;i<n;i++){int x,y,v;cin>>x>>y>>v;
  ld lo=max(-R,(ld)-x), hi=min(R,(ld)(w-x));
  ld area=F(h-y,lo,hi)+F(y,lo,hi);
  tot+=v*area;}
 printf("%.12Lf\n",tot/((ld)w*h));}
