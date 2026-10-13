#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);while(n--){long long l1,a1,l2,a2,lt,at;scanf("%lld %lld %lld %lld %lld %lld",&l1,&a1,&l2,&a2,&lt,&at);
 int cnt=0;long long bx=0,by=0;
 for(long long x=1;x*l1<lt&&x*a1<at;x++){long long r=lt-x*l1;if(r%l2)continue;long long y=r/l2;if(y<1)continue;if(x*a1+y*a2==at){cnt++;bx=x;by=y;}}
 if(cnt==1)printf("%lld %lld\n",bx,by);else puts("?");}}
