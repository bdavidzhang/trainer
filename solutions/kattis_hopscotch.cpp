#include <bits/stdc++.h>
using namespace std;
typedef long long ll;const ll M=1e9+7;
ll pw(ll b,ll e){ll r=1;b%=M;while(e){if(e&1)r=r*b%M;b=b*b%M;e>>=1;}return r;}
int main(){ll N,X,Y;cin>>N>>X>>Y;int S=2*N+5;vector<ll> f(S),g(S);f[0]=1;for(int i=1;i<S;i++)f[i]=f[i-1]*i%M;
  g[S-1]=pw(f[S-1],M-2);for(int i=S-1;i>0;i--)g[i-1]=g[i]*i%M;
  auto C=[&](ll n,ll k)->ll{if(k<0||n<k||n<0)return 0;return f[n]*g[k]%M*g[n-k]%M;};
  ll ans=0;
  for(ll k=1;k*X<=N&&k*Y<=N;k++){ans=(ans+C(N-k*X+k-1,k-1)*C(N-k*Y+k-1,k-1))%M;}
  cout<<ans<<endl;}
