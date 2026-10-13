#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){ll n,p;scanf("%lld %lld",&n,&p);vector<int> pw(n+1);pw[0]=1%p;for(int i=1;i<=n;i++)pw[i]=(ll)pw[i-1]*2%p;
 ll s=0;for(ll d=1;d<n;d++){ll g=std::gcd(d,n);s=(s+pw[g]-2+p)%p;}
 ll ans=s%p*((n-2)%p)%p*((p+1)/2)%p;printf("%lld\n",ans);}
