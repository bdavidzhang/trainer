#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;scanf("%d",&n);vector<ll>x(n),y(n);int p=0;for(int i=0;i<n;i++){scanf("%lld %lld",&x[i],&y[i]);if(y[i]>y[p])p=i;}
 for(int dir=-1;dir<=1;dir+=2){int best=-1,mn=-1; // mn: index with minimal slope so far
  for(int i=p+dir;i>=0&&i<n;i+=dir){ll dy=y[p]-y[i],dx=llabs(x[p]-x[i]);bool vis;
   if(mn<0)vis=true;else{ll dy2=y[p]-y[mn],dx2=llabs(x[p]-x[mn]);vis=(dy*dx2<=dy2*dx);}
   if(vis){mn=i;if(best<0||y[i]<=y[best])best=i;}}
  printf("%lld %lld\n",x[best],y[best]);}
}
