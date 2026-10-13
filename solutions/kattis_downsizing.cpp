#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
int main(){
    ld x0,y0,r;int n;
    {double a,b,c;scanf("%lf %lf %lf %d",&a,&b,&c,&n);x0=a;y0=b;r=c;}
    vector<ld>x(n),y(n);
    for(int i=0;i<n;i++){double a,b;scanf("%lf %lf",&a,&b);x[i]=a-x0;y[i]=b-y0;}
    ld tot=0;
    auto F=[](ld u){return u/2+sinl(2*u)/4;};
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        ld ax=x[i],ay=y[i],bx=x[j],by=y[j];
        ld len=hypotl(bx-ax,by-ay);
        if(len==0)continue;
        ld cr=ax*by-ay*bx;
        if(cr==0)continue; // edge on a line through O: no angular extent
        ld ex=(bx-ax)/len,ey=(by-ay)/len;
        ld D=fabsl(cr)/len;
        ld tA=ax*ex+ay*ey,tB=bx*ex+by*ey;
        ld I=(F(atan2l(tB,D))-F(atan2l(tA,D)))/(D*D);
        tot+=(cr>0?1:-1)*I;
    }
    ld area=fabsl(tot)*r*r*r*r/2;
    printf("%.9Lf\n",area);
}
