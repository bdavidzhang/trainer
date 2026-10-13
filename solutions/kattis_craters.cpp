#include <bits/stdc++.h>
using namespace std;
typedef double D;typedef long long ll;
struct Pt{D x,y;int c;};
D cross(const Pt&o,const Pt&a,const Pt&b){return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);}
int main(){int n;scanf("%d",&n);vector<ll> x(n),y(n),r(n);for(int i=0;i<n;i++){scanf("%lld %lld %lld",&x[i],&y[i],&r[i]);r[i]+=10;}
 vector<int> keep;
 for(int i=0;i<n;i++){bool rem=false;for(int j=0;j<n&&!rem;j++)if(j!=i){ll d2=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
   if(r[j]>=r[i]&&d2<=(r[j]-r[i])*(r[j]-r[i])){if(r[j]==r[i]&&d2==0&&j>i)continue;rem=true;}}
  if(!rem)keep.push_back(i);}
 const D PI=acos(-1.0);int k=keep.size();
 if(k==1){printf("%.8f\n",2*PI*r[keep[0]]);return 0;}
 vector<Pt> pts;
 for(int a=0;a<k;a++)for(int b=a+1;b<k;b++){int i=keep[a],j=keep[b];D dx=x[j]-x[i],dy=y[j]-y[i];D d=sqrt(dx*dx+dy*dy);
  D phi=atan2(dy,dx);D al=acos(max(-1.0,min(1.0,(D)(r[i]-r[j])/d)));
  for(int s=-1;s<=1;s+=2){D t=phi+s*al;D nx=cos(t),ny=sin(t);bool sup=true;
   for(int c=0;c<k&&sup;c++){int q=keep[c];if((x[q]-x[i])*nx+(y[q]-y[i])*ny+r[q]>r[i]+1e-7)sup=false;}
   if(!sup)continue;pts.push_back({x[i]+r[i]*cos(t),y[i]+r[i]*sin(t),i});pts.push_back({x[j]+r[j]*cos(t),y[j]+r[j]*sin(t),j});}}
 sort(pts.begin(),pts.end(),[](const Pt&a,const Pt&b){return a.x<b.x||(a.x==b.x&&a.y<b.y);});
 int m=pts.size();vector<Pt> h(2*m);int sz=0;
 for(int i=0;i<m;i++){while(sz>=2&&cross(h[sz-2],h[sz-1],pts[i])<=0)sz--;h[sz++]=pts[i];}
 for(int i=m-2,t=sz+1;i>=0;i--){while(sz>=t&&cross(h[sz-2],h[sz-1],pts[i])<=0)sz--;h[sz++]=pts[i];}
 sz--;D ans=0;
 for(int i=0;i<sz;i++){Pt&p=h[i],&q=h[(i+1)%sz];
  if(p.c==q.c){D a1=atan2(p.y-y[p.c],p.x-x[p.c]),a2=atan2(q.y-y[q.c],q.x-x[q.c]);D da=a2-a1;while(da<0)da+=2*PI;while(da>=2*PI)da-=2*PI;
   if(da>2*PI-1e-7)da=0;ans+=da*r[p.c];}
  else ans+=hypot(p.x-q.x,p.y-q.y);}
 printf("%.8f\n",ans);}
