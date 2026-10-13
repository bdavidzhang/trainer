#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;ll k;scanf("%d %lld",&n,&k);vector<ll>p(n);ll mx=0;for(auto&x:p){scanf("%lld",&x);mx=max(mx,x);}
 ll lo=1,hi=mx;while(lo<hi){ll m=lo+(hi-lo)/2;__int128 c=0;for(ll x:p)c+=(x+m-1)/m;if(c<=k)hi=m;else lo=m+1;}
 printf("%lld\n",lo);}
