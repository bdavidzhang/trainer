#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int t;scanf("%d",&t);while(t--){ll n,k,a,b;scanf("%lld %lld %lld %lld",&n,&k,&a,&b);ll d=b-a,ans=0;bool ok=true;
 while(k>0){ll g=n*d/a;if(g==0){ok=false;break;}
  if(g>=k){ans++;break;}
  ll nn=((g+1)*a+d-1)/d; // first n with gain g+1
  ll s1=(nn-n+g-1)/g, s2=(k+g-1)/g; ll s=min(s1,s2); if(s<1)s=1;
  n+=s*g;k-=s*g;ans+=s;}
 printf("%lld\n",ok?ans:-1LL);}
}
