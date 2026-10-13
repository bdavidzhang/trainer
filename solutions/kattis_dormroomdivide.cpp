#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;scanf("%d",&n);vector<ll>x(n),y(n);for(int i=0;i<n;i++)scanf("%lld %lld",&x[i],&y[i]);
 vector<ll>tr(n,0);ll S=0;for(int i=1;i+1<n;i++){tr[i]=(x[i]-x[0])*(y[i+1]-y[0])-(x[i+1]-x[0])*(y[i]-y[0]);S+=tr[i];}
 ll pre=0;for(int i=1;i+1<n;i++){if(2*(pre+tr[i])>=S){long double f=(long double)(S-2*pre)/(2.0L*tr[i]);
   long double X=x[i]+f*(x[i+1]-x[i]),Y=y[i]+f*(y[i+1]-y[i]);printf("%.9Lf %.9Lf\n",X,Y);return 0;}pre+=tr[i];}
 }
