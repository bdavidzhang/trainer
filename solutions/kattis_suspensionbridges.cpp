#include <bits/stdc++.h>
using namespace std;
int main(){double d,s;cin>>d>>s;
 // f(a)=a*(cosh(d/2a)-1)-s is decreasing in a
 double lo=d/1400.0,hi=1e9;
 for(int it=0;it<200;it++){double a=(lo+hi)/2;double h=sinh(d/(4*a));double f=a*2*h*h-s;if(f>0)lo=a;else hi=a;}
 double a=(lo+hi)/2;printf("%.9f\n",2*a*sinh(d/(2*a)));
}
