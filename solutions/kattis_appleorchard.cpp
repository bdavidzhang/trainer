#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const double PI=acos(-1.0), TAU=2*acos(-1.0);
struct Circ{ ll x,y,r; vector<pair<double,double>> arcs; };
// theta - sin(theta), accurate for small theta
static inline double segf(double t){
    if(t<0.02){ double t2=t*t; return t*t2*(1.0/6-t2*(1.0/120-t2*(1.0/5040-t2/362880.0))); }
    return t-sin(t);
}
static double unionLen(vector<pair<double,double>>&v){
    if(v.empty()) return 0;
    sort(v.begin(),v.end());
    double tot=0,cs=v[0].first,ce=v[0].second;
    for(size_t i=1;i<v.size();i++){
        if(v[i].first>ce){tot+=ce-cs;cs=v[i].first;ce=v[i].second;}
        else if(v[i].second>ce) ce=v[i].second;
    }
    return tot+ce-cs;
}
int main(){
    int n,q; scanf("%d %d",&n,&q);
    vector<array<ll,3>> in(n);
    for(auto&c:in) scanf("%lld %lld %lld",&c[0],&c[1],&c[2]);
    sort(in.begin(),in.end()); in.erase(unique(in.begin(),in.end()),in.end());
    n=in.size();
    vector<Circ> cs;
    for(int i=0;i<n;i++){
        bool inside=false;
        for(int j=0;j<n&&!inside;j++) if(j!=i && in[j][2]>=in[i][2]){
            ll dx=in[i][0]-in[j][0],dy=in[i][1]-in[j][1],dr=in[j][2]-in[i][2];
            if(dx*dx+dy*dy<=dr*dr) inside=true;
        }
        if(!inside) cs.push_back({in[i][0],in[i][1],in[i][2],{}});
    }
    n=cs.size();
    vector<pair<double,double>> cov;
    for(int i=0;i<n;i++){
        cov.clear();
        ll ri=cs[i].r;
        for(int j=0;j<n;j++) if(j!=i){
            ll dx=cs[j].x-cs[i].x,dy=cs[j].y-cs[i].y,rj=cs[j].r;
            ll d2=dx*dx+dy*dy;
            if(d2>=(ri+rj)*(ri+rj)) continue;
            ll N=d2+ri*ri-rj*rj;
            __int128 num=(__int128)4*d2*ri*ri-(__int128)N*N;
            if(num<=0) continue;
            ld d=sqrtl((ld)d2);
            ld a=(ld)N/(2*d), h=sqrtl((ld)num)/(2*d);
            double alpha=(double)atan2l(h,a), phi=atan2((double)dy,(double)dx);
            double lo=phi-alpha,hi=phi+alpha;
            if(lo<0){lo+=TAU;hi+=TAU;}
            if(hi>TAU){cov.push_back({lo,TAU});cov.push_back({0,hi-TAU});}
            else cov.push_back({lo,hi});
        }
        sort(cov.begin(),cov.end());
        double cur=0;
        for(auto&c:cov){
            if(c.first>cur) cs[i].arcs.push_back({cur,c.first});
            if(c.second>cur) cur=c.second;
        }
        if(cur<TAU) cs[i].arcs.push_back({cur,TAU});
    }
    vector<pair<double,double>> R,T,ins;
    double ang[8];
    while(q--){
        ll x0,y0,w,h; scanf("%lld %lld %lld %lld",&x0,&y0,&w,&h);
        R.clear();T.clear();
        bool full=false; double tot=0;
        for(int i=0;i<n&&!full;i++){
            const Circ&c=cs[i];
            ll X=c.x-x0,Y=c.y-y0,r=c.r,r2=r*r;
            if(X+r<=0||X-r>=w||Y+r<=0||Y-r>=h) continue;
            ll fx=max(llabs(X),llabs(X-w)),fy=max(llabs(Y),llabs(Y-h));
            if(fx*fx+fy*fy<=r2){full=true;break;}
            int m=0;
            {   // right edge x=w
                ll dx=w-X;
                if(llabs(dx)<r){
                    double s=sqrt((double)(r2-dx*dx));
                    double lo=max(0.0,Y-s),hi=min((double)h,Y+s);
                    if(lo<hi) R.push_back({lo,hi});
                    if(Y+s>=0&&Y+s<=h) ang[m++]=atan2(s,(double)dx);
                    if(Y-s>=0&&Y-s<=h) ang[m++]=atan2(-s,(double)dx);
                }
            }
            {   // top edge y=h
                ll dy=h-Y;
                if(llabs(dy)<r){
                    double s=sqrt((double)(r2-dy*dy));
                    double lo=max(0.0,X-s),hi=min((double)w,X+s);
                    if(lo<hi) T.push_back({lo,hi});
                    if(X+s>=0&&X+s<=w) ang[m++]=atan2((double)dy,s);
                    if(X-s>=0&&X-s<=w) ang[m++]=atan2((double)dy,-s);
                }
            }
            if(c.arcs.empty()) continue;
            if(llabs(X)<r){
                double s=sqrt((double)(r2-X*X));
                if(Y+s>=0&&Y+s<=h) ang[m++]=atan2(s,(double)-X);
                if(Y-s>=0&&Y-s<=h) ang[m++]=atan2(-s,(double)-X);
            }
            if(llabs(Y)<r){
                double s=sqrt((double)(r2-Y*Y));
                if(X+s>=0&&X+s<=w) ang[m++]=atan2((double)-Y,s);
                if(X-s>=0&&X-s<=w) ang[m++]=atan2((double)-Y,-s);
            }
            ins.clear();
            if(m==0){
                if(X-r>=0&&X+r<=w&&Y-r>=0&&Y+r<=h) ins.push_back({0,TAU});
            } else {
                for(int k=0;k<m;k++) if(ang[k]<0) ang[k]+=TAU;
                sort(ang,ang+m);
                for(int k=0;k<m;k++){
                    double t1=ang[k],t2=k+1<m?ang[k+1]:ang[0]+TAU;
                    if(t2-t1<1e-15) continue;
                    double mid=(t1+t2)/2;
                    double px=X+r*cos(mid),py=Y+r*sin(mid);
                    if(px<0||px>w||py<0||py>h) continue;
                    if(t2>TAU){ins.push_back({t1,TAU});ins.push_back({0,t2-TAU});}
                    else ins.push_back({t1,t2});
                }
            }
            double rr=(double)r2;
            for(auto&iv:ins) for(auto&a:c.arcs){
                double lo=max(iv.first,a.first),hi=min(iv.second,a.second);
                if(hi<=lo) continue;
                double p1x=X+r*cos(lo),p1y=Y+r*sin(lo),p2x=X+r*cos(hi),p2y=Y+r*sin(hi);
                tot+=p1x*p2y-p1y*p2x+rr*segf(hi-lo);
            }
        }
        double pct;
        if(full) pct=100;
        else{
            tot+=(double)w*unionLen(R)+(double)h*unionLen(T);
            pct=tot/2/((double)w*h)*100;
            if(pct<0)pct=0; if(pct>100)pct=100;
        }
        printf("%.10f\n",pct);
    }
}
