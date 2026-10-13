#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);long long a=LLONG_MAX,b=LLONG_MAX,c=LLONG_MIN,d=LLONG_MIN;for(int i=0;i<n;i++){long long x,y;scanf("%lld %lld",&x,&y);a=min(a,x);b=min(b,y);c=max(c,x);d=max(d,y);}
 // any enclosing rectilinear closed path is at least as long as the bounding box perimeter
 printf("4\n%lld %lld\n%lld %lld\n%lld %lld\n%lld %lld\n",a,b,c,b,c,d,a,d);}
