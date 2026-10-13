#include <bits/stdc++.h>
using namespace std;
int main(){double l,a,b;cin>>l>>a>>b;long long L=llround(l*10),A=llround(a*10),B=llround(b*10);
 long long best=-1,bx=0,by=0;
 for(long long x=0;x*A<=L;x++){long long y=(L-x*A)/B;long long t=x*A+y*B;if(t>=best){best=t;bx=x;by=y;}}
 printf("%lld %lld\n",bx,by);}
