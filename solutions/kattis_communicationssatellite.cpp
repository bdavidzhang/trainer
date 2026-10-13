#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<double>x(n),y(n),r(n);for(int i=0;i<n;i++)scanf("%lf %lf %lf",&x[i],&y[i],&r[i]);
vector<double>d(n,1e18);vector<char>u(n,0);d[0]=0;double tot=0;
for(int it=0;it<n;it++){int b=-1;for(int i=0;i<n;i++)if(!u[i]&&(b<0||d[i]<d[b]))b=i;u[b]=1;tot+=d[b];
for(int i=0;i<n;i++)if(!u[i]){double w=max(0.0,hypot(x[i]-x[b],y[i]-y[b])-r[i]-r[b]);if(w<d[i])d[i]=w;}}
printf("%.8f\n",tot);}
