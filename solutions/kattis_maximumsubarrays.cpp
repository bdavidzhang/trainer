#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n,k;scanf("%d %d",&n,&k);vector<ll>a(n);for(auto&x:a)scanf("%lld",&x);
const ll NEG=LLONG_MIN/4;
// f[j]: best using first i elems with j subarrays, last one ends exactly at i; g[j]: best with j subarrays within first i
vector<ll> f(k+1,NEG),g(k+1,NEG);g[0]=0;
for(int i=0;i<n;i++){for(int j=min(k,i+1);j>=1;j--){ll b=max(f[j],g[j-1]);f[j]=b<=NEG?NEG:b+a[i];g[j]=max(g[j],f[j]);}}
printf("%lld\n",g[k]);}
