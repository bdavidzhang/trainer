#include <bits/stdc++.h>
using namespace std;
int main(){ int n; cin>>n; vector<double>x(n),y(n),r(n); for(int i=0;i<n;i++)cin>>x[i]>>y[i]>>r[i];
    const double h=0.02; long long cnt=0;
    for(double px=-10+h/2;px<20;px+=h) for(double py=-10+h/2;py<20;py+=h){
        for(int i=0;i<n;i++){ double dx=px-x[i],dy=py-y[i]; if(dx*dx+dy*dy<=r[i]*r[i]){cnt++;break;} }
    }
    printf("%.6f\n",cnt*h*h); }
