#include <bits/stdc++.h>
using namespace std;
int main(){double x1,y1,x2,y2,a;cin>>x1>>y1>>x2>>y2>>a;
 double A=a/2,dx=x2-x1,dy=y2-y1,d=sqrt(dx*dx+dy*dy),c=d/2;
 double b2=max(0.0,A*A-c*c);
 double cs=1,sn=0;if(d>0){cs=dx/d;sn=dy/d;}
 double hx=sqrt(A*A*cs*cs+b2*sn*sn),hy=sqrt(A*A*sn*sn+b2*cs*cs);
 double cx=(x1+x2)/2,cy=(y1+y2)/2;
 printf("%.8f %.8f %.8f %.8f\n",cx-hx,cy-hy,cx+hx,cy+hy);}
