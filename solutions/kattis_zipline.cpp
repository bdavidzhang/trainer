#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);while(n--){long double w,g,h,r;double a,b,c,d;scanf("%lf %lf %lf %lf",&a,&b,&c,&d);w=a;g=b;h=c;r=d;
 printf("%.8Lf %.8Lf\n",sqrtl(w*w+(g-h)*(g-h)),sqrtl(w*w+(g+h-2*r)*(g+h-2*r)));}}
