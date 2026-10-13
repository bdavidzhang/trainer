#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<double>x(n),y(n);for(int i=0;i<n;i++)scanf("%lf %lf",&x[i],&y[i]);
 double best=1e18;
 for(int i=0;i<n;i++){int j=(i+1)%n;double dx=x[j]-x[i],dy=y[j]-y[i],L=hypot(dx,dy),m=0;
  for(int k=0;k<n;k++)m=max(m,fabs(dx*(y[k]-y[i])-dy*(x[k]-x[i]))/L);
  best=min(best,m);}
 printf("%.8f\n",best);}
