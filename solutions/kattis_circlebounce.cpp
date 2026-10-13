#include <bits/stdc++.h>
using namespace std;
typedef long long ll;const ll M=1000000007;
ll pw(ll b,ll e){ll r=1;b%=M;while(e){if(e&1)r=r*b%M;b=b*b%M;e>>=1;}return r;}
int main(){ll a,b,n;cin>>a>>b>>n;
 // x = (-1)^n * Re( ((b+ai)^2/(a^2+b^2))^(n+1) )
 ll inv=pw((a%M*a+b%M*b)%M,M-2);
 ll re=((b*b-a%M*a)%M+M)%M*inv%M, im=2*a%M*b%M*inv%M;
 ll rr=1,ri=0;ll e=n+1;
 while(e){if(e&1){ll x=(rr*re-ri*im%M+M*M)%M,y=(rr*im+ri*re)%M;rr=x;ri=y;}
  ll x=(re*re-im*im%M+M*M)%M,y=2*re*im%M;re=x;im=y;e>>=1;}
 if(n&1)rr=(M-rr)%M;
 cout<<rr<<endl;}
