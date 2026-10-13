#include <bits/stdc++.h>
using namespace std;
// area of good camera positions in the right arm: b^2 <= h^2 - D*h*(a-w)/w
static double F(double W,double H,double w,double h){
    double D=H-h, c=D*h/w;
    double U=min(W-w, h*w/D);
    double rem=h*h-c*U; if(rem<0) rem=0;
    return 2.0/(3.0*c)*(h*h*h-pow(rem,1.5));
}
int main(){
    int n; scanf("%d",&n);
    vector<long long> x(n),y(n);
    for(int i=0;i<n;i++) scanf("%lld %lld",&x[i],&y[i]);
    long long x0=*min_element(x.begin(),x.end()),x1=*max_element(x.begin(),x.end());
    long long y0=*min_element(y.begin(),y.end()),y1=*max_element(y.begin(),y.end());
    if(n==4){ printf("%.9f\n",(double)((x1-x0)*(y1-y0))); return 0; }
    // reflex vertex: strictly inside bounding box
    long long rx=0,ry=0;
    for(int i=0;i<n;i++) if(x[i]>x0&&x[i]<x1&&y[i]>y0&&y[i]<y1){rx=x[i];ry=y[i];}
    // missing bbox corner
    auto has=[&](long long a,long long b){for(int i=0;i<n;i++) if(x[i]==a&&y[i]==b) return true; return false;};
    double W=x1-x0,H=y1-y0,w,h;
    bool right = !has(x1,y0) || !has(x1,y1);
    bool top = !has(x0,y1) || !has(x1,y1);
    w = right ? rx-x0 : x1-rx;
    h = top ? ry-y0 : y1-ry;
    double ans=w*h+F(W,H,w,h)+F(H,W,h,w);
    printf("%.9f\n",ans);
}
