#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){ll n,k,p;cin>>n>>k>>p;vector<ll>r;
 for(ll d=1;d*d<=n;d++)if(n%d==0){ll e=n/d;if(d<=k&&e<=p)r.push_back(d);if(e!=d&&e<=k&&d<=p)r.push_back(e);}
 sort(r.begin(),r.end());printf("%d\n",(int)r.size());for(ll x:r)printf("%lld\n",x);}
