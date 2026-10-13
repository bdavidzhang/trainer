#include <bits/stdc++.h>
using namespace std;
int main(){int n;long long t;cin>>n>>t;vector<double>x(n),y(n);vector<long long>tm(n);
 for(int i=0;i<n;i++)cin>>x[i]>>y[i]>>tm[i];
 double real=0;for(int i=1;i<n;i++)real+=hypot(x[i]-x[i-1],y[i]-y[i-1]);
 double gps=0,px=x[0],py=y[0];int j=0;long long T=tm[n-1];
 for(long long c=t;c<T;c+=t){while(tm[j+1]<c)j++;
  double f=double(c-tm[j])/double(tm[j+1]-tm[j]);
  double qx=x[j]+(x[j+1]-x[j])*f,qy=y[j]+(y[j+1]-y[j])*f;
  gps+=hypot(qx-px,qy-py);px=qx;py=qy;}
 gps+=hypot(x[n-1]-px,y[n-1]-py);
 printf("%.10f\n",(real-gps)/real*100);
}
