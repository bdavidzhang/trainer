#include <bits/stdc++.h>
using namespace std;
int main(){long long r,s,h;cin>>r>>s>>h;long double T=2.0L*acosl(-1.0L)*r/((long double)s*h);
 long double d=floorl(T+0.5L);long double f=fabsl(T-d);
 long double best=1e18;int b1=0,b2=0,b3=0;
 for(int n1=2;n1<=1000;n1++)for(int n2=2*n1;n2<=1000;n2+=n1)for(int n3=2*n2;n3<=1000;n3+=n2){
  long double v=1.0L/n1-1.0L/n2+1.0L/n3;long double e=fabsl(v-f);if(e<best){best=e;b1=n1;b2=n2;b3=n3;}}
 printf("%d %d %d\n",b1,b2,b3);}
