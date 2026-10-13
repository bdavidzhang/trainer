#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<long long> x(n),y(n),r(n);
    for(int i=0;i<n;i++) scanf("%lld %lld %lld",&x[i],&y[i],&r[i]);
    const double PI=acos(-1.0);
    double ans=0;
    for(int i=0;i<n;i++){
        bool gone=false;
        vector<pair<double,double>> iv;
        for(int j=i+1;j<n&&!gone;j++){
            long long dx=x[j]-x[i],dy=y[j]-y[i];
            long long d2=dx*dx+dy*dy;
            if(r[j]>=r[i] && d2<=(r[j]-r[i])*(r[j]-r[i])){gone=true;break;} // i inside/on j
            if(d2>=(r[i]+r[j])*(r[i]+r[j])) continue; // disjoint / ext tangent
            if(r[i]>r[j] && d2<=(r[i]-r[j])*(r[i]-r[j])) continue; // j inside i
            double d=sqrt((double)d2);
            double c=((double)d2+(double)(r[i]*r[i])-(double)(r[j]*r[j]))/(2.0*d*r[i]);
            c=max(-1.0,min(1.0,c));
            double h=acos(c), a=atan2((double)dy,(double)dx);
            double lo=a-h,hi=a+h;
            if(lo<-PI){iv.push_back({lo+2*PI,PI});iv.push_back({-PI,hi});}
            else if(hi>PI){iv.push_back({lo,PI});iv.push_back({-PI,hi-2*PI});}
            else iv.push_back({lo,hi});
        }
        if(gone) continue;
        sort(iv.begin(),iv.end());
        double cov=0,cur=-PI;
        for(auto&p:iv){
            if(p.second<=cur) continue;
            cov+=p.second-max(cur,p.first);
            cur=p.second;
        }
        ans+=(2*PI-cov)*r[i];
    }
    printf("%.9f\n",ans);
}
