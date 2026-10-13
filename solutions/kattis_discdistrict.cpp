#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){ll r;scanf("%lld",&r);ll best=LLONG_MAX,bx=0,by=0;
for(ll x=0;x<=r;x++){ll rem=r*r-x*x;ll y=(ll)sqrtl((long double)rem);while(y*y>rem)y--;while((y+1)*(y+1)<=rem)y++;y++;
 ll d=x*x+y*y;if(d<best){best=d;bx=x;by=y;}}
printf("%lld %lld\n",bx,by);}
