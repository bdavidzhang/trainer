#include <bits/stdc++.h>
using namespace std;
int main(){int t;scanf("%d",&t);while(t--){long double R,a,b;double x,y,z;scanf("%lf %lf %lf",&x,&y,&z);R=x;a=y/1000.0L;b=z/1000.0L;
 // acos(R/(R+h)) computed stably as atan2(sqrt(h(2R+h)),R)
 long double d=R*(atan2l(sqrtl(a*(2*R+a)),R)+atan2l(sqrtl(b*(2*R+b)),R));printf("%.12Lf\n",d);}}
