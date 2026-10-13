#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n,k;scanf("%d %d",&n,&k);vector<ll>t(n);for(auto&x:t)scanf("%lld",&x);sort(t.begin(),t.end());
 int d=min(n,k);
 auto ok=[&](ll T){ll c=0;for(int i=0;i<d&&c<n;i++){if(T<t[i])break;c+=1+4*(1+(T-t[i])/(2*t[i]));}return c>=n;};
 ll lo=0,hi=t[0]*(2LL*n+3);
 while(lo<hi){ll m=(lo+hi)/2;if(ok(m))hi=m;else lo=m+1;}
 printf("%lld\n",lo);}
