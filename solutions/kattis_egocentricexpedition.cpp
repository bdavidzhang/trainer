#include <bits/stdc++.h>
using namespace std;
int main(){int t;if(scanf("%d",&t)!=1)return 0;
 while(t--){double d1,d2;
  printf("? 1 0\n");fflush(stdout);if(scanf("%lf",&d1)!=1)return 0;
  printf("? 1 1\n");fflush(stdout);if(scanf("%lf",&d2)!=1)return 0;
  // d1=h/cos(b), d2=h/cos(45deg-b), b in [0,45deg]  => tan b = sqrt2*d1/d2-1
  double tb=sqrt(2.0)*d1/d2-1.0;
  double A=4.0*d1*d1/(1.0+tb*tb);
  long long r=llround(A); if(r<1)r=1;
  printf("! %lld\n",r);fflush(stdout);
 }
}
