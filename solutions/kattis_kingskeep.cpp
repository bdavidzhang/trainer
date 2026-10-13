#include <bits/stdc++.h>
using namespace std;
int main(){int k;scanf("%d",&k);vector<double>x(k),y(k);for(int i=0;i<k;i++)scanf("%lf %lf",&x[i],&y[i]);
double best=1e18;for(int i=0;i<k;i++){double s=0;for(int j=0;j<k;j++)s+=hypot(x[i]-x[j],y[i]-y[j]);best=min(best,s);}
printf("%.9f\n",best/(k-1));}
