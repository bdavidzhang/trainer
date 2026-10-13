#include <bits/stdc++.h>
using namespace std;
typedef double D;
struct P{D x,y;};
int n;vector<vector<P>> poly;
bool inside(const vector<P>&p,D x,D y){bool in=false;int m=p.size();
 for(int i=0,j=m-1;i<m;j=i++){if((p[i].y>y)!=(p[j].y>y)){D xi=p[j].x+(y-p[j].y)*(p[i].x-p[j].x)/(p[i].y-p[j].y);if(xi>x)in=!in;}}
 return in;}
int main(){scanf("%d",&n);poly.resize(n);D paint=0;
 for(int i=0;i<n;i++){int m;scanf("%d",&m);poly[i].resize(m);for(auto&p:poly[i])scanf("%lf %lf",&p.x,&p.y);
  D a=0;for(int k=0;k<m;k++){P&p=poly[i][k],&q=poly[i][(k+1)%m];a+=p.x*q.y-p.y*q.x;}
  if(a<0){reverse(poly[i].begin(),poly[i].end());a=-a;}paint+=a/2;}
 D uni=0;
 for(int i=0;i<n;i++){int m=poly[i].size();
  for(int k=0;k<m;k++){P A=poly[i][k],B=poly[i][(k+1)%m];D dx=B.x-A.x,dy=B.y-A.y;
   vector<pair<D,D>> cov;
   for(int j=0;j<n;j++)if(j!=i){const auto&q=poly[j];int mj=q.size();vector<D> ts={0,1};
    for(int e=0;e<mj;e++){P C=q[e],E=q[(e+1)%mj];D ex=E.x-C.x,ey=E.y-C.y;D den=dx*ey-dy*ex;if(fabs(den)<1e-12)continue;
     D t=((C.x-A.x)*ey-(C.y-A.y)*ex)/den;D s=((C.x-A.x)*dy-(C.y-A.y)*dx)/den;
     if(t>0&&t<1&&s>=-1e-12&&s<=1+1e-12)ts.push_back(t);}
    sort(ts.begin(),ts.end());
    for(size_t z=0;z+1<ts.size();z++){if(ts[z+1]-ts[z]<1e-12)continue;D tm=(ts[z]+ts[z+1])/2;
     if(inside(q,A.x+dx*tm,A.y+dy*tm))cov.push_back({ts[z],ts[z+1]});}}
   sort(cov.begin(),cov.end());D covered=0,cur=0;
   for(auto&c:cov){D l=max(c.first,cur);if(c.second>l){covered+=c.second-l;cur=c.second;}}
   uni+=(A.x*B.y-A.y*B.x)*(1-covered)/2;}}
 printf("%.8f %.8f\n",paint,uni);}
