#include <bits/stdc++.h>
using namespace std;
double R;
double S(double t){t=max(-R,min(R,t));return (t*sqrt(max(0.0,R*R-t*t))+R*R*asin(t/R))/2;}
// area of disk with X<=x, Y<=y
double G(double x,double y){
    x=max(-R,min(R,x));y=max(-R,min(R,y));
    double a=sqrt(max(0.0,R*R-y*y));
    double lo=-a,hi=min(a,x);
    double part=0;
    if(y>=0){
        double full=2*(S(x)-S(-R));
        if(hi>lo)part=(S(hi)-S(lo))-y*(hi-lo);
        return full-part;
    }else{
        if(hi>lo)part=(S(hi)-S(lo))+y*(hi-lo);
        return part;
    }
}
int main(){
    double rr,ddx,ddy,xx,yy,p;cin>>rr>>ddx>>ddy>>xx>>yy>>p;
    long long r=llround(rr),dx=llround(ddx),dy=llround(ddy),x=llround(xx),y=llround(yy);
    R=r;
    auto lines=[&](long long o,long long d){
        vector<long long> v;v.push_back(-r);
        long long k=((o%d)+d)%d; // residue
        // smallest value > -r congruent to k mod d
        long long s=-r+((k-(-r))%d+d)%d;if(s==-r)s+=d;
        for(;s<r;s+=d)v.push_back(s);
        v.push_back(r);return v;
    };
    auto X=lines(x,dx),Y=lines(y,dy);
    int nx=X.size(),ny=Y.size();
    vector<vector<double>> g(nx,vector<double>(ny));
    for(int i=0;i<nx;i++)for(int j=0;j<ny;j++)g[i][j]=G(X[i],Y[j]);
    vector<double> ar;double mx=0;
    for(int i=0;i+1<nx;i++)for(int j=0;j+1<ny;j++){
        long long cx=0,cy=0;
        if(X[i]>0)cx=X[i];else if(X[i+1]<0)cx=X[i+1];
        if(Y[j]>0)cy=Y[j];else if(Y[j+1]<0)cy=Y[j+1];
        if(cx*cx+cy*cy>=r*r)continue;
        double a=g[i+1][j+1]-g[i][j+1]-g[i+1][j]+g[i][j];
        if(a<0)a=0;
        ar.push_back(a);mx=max(mx,a);
    }
    long long cnt=0;
    for(double a:ar)if(a/mx<=p+1e-6)cnt++;
    printf("%lld\n",cnt);
}
