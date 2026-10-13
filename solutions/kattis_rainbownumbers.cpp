#include <bits/stdc++.h>
using namespace std;
typedef long long ll;const ll M=998244353;
vector<ll> p9;
ll cnt(const string&x){int n=x.size();ll r=0;for(int k=1;k<n;k++)r=(r+p9[k])%M;
 bool ok=true;for(int i=0;i<n;i++){int d=x[i]-'0';int prev=i?x[i-1]-'0':-1;int c=0;for(int e=(i==0?1:0);e<d;e++)if(e!=prev)c++;
  r=(r+c*p9[n-1-i])%M;if(d==prev){ok=false;break;}}
 if(ok)r=(r+1)%M;return r;}
bool rb(const string&x){for(size_t i=1;i<x.size();i++)if(x[i]==x[i-1])return false;return true;}
int main(){string L,U;cin>>L>>U;p9.assign(max(L.size(),U.size())+2,1);for(size_t i=1;i<p9.size();i++)p9[i]=p9[i-1]*9%M;
 ll a=(cnt(U)-cnt(L)+(rb(L)?1:0)+2*M)%M;printf("%lld\n",a);}
