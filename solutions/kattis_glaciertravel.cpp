#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
int main(){double sd;int n;scanf("%lf %d",&sd,&n);ld s=sd;vector<ld>x(n),y(n);
 for(int i=0;i<n;i++){int a,b;scanf("%d %d",&a,&b);x[i]=a;y[i]=b;}
 int m=n-1;vector<ld>len(m),ux(m),uy(m);
 for(int i=0;i<m;i++){ld dx=x[i+1]-x[i],dy=y[i+1]-y[i];len[i]=sqrtl(dx*dx+dy*dy);ux[i]=dx/len[i];uy[i]=dy/len[i];}
 int i=0,j=0;ld oa=0,ob=0,rem=s;
 while(j<m-1&&rem>len[j]){rem-=len[j];j++;}
 ob=min(rem,len[j]);
 ld best=1e30L;const ld EPS=1e-12L;
 while(true){
  ld ra=len[i]-oa,rb=len[j]-ob;if(ra<0)ra=0;if(rb<0)rb=0;
  ld st=min(ra,rb);
  ld Dx=(x[j]+ux[j]*ob)-(x[i]+ux[i]*oa),Dy=(y[j]+uy[j]*ob)-(y[i]+uy[i]*oa);
  ld wx=ux[j]-ux[i],wy=uy[j]-uy[i];ld w2=wx*wx+wy*wy;ld t=0;
  if(w2>1e-30L){t=-(Dx*wx+Dy*wy)/w2;if(t<0)t=0;if(t>st)t=st;}
  for(ld tt:{(ld)0,t,st}){ld ex=Dx+wx*tt,ey=Dy+wy*tt;best=min(best,sqrtl(ex*ex+ey*ey));}
  bool fa=(ra-st)<=EPS*(1+len[i]),fb=(rb-st)<=EPS*(1+len[j]);
  if(fb&&j==m-1)break;
  oa+=st;ob+=st;
  if(fa){i++;oa=0;}
  if(fb){j++;ob=0;}
 }
 printf("%.9Lf\n",best);}
