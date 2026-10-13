#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;scanf("%d",&n);vector<ll>h(n);for(auto&x:h)scanf("%lld",&x);
vector<ll> L(n),R(n);L[0]=h[0];for(int i=1;i<n;i++)L[i]=h[i-1]<=h[i]?L[i-1]:h[i];
R[n-1]=h[n-1];for(int i=n-2;i>=0;i--)R[i]=h[i+1]<=h[i]?R[i+1]:h[i];
ll ans=0;for(int j=1;j+1<n;j++)if(h[j-1]<=h[j]&&h[j]>=h[j+1])ans=max(ans,min(h[j]-L[j],h[j]-R[j]));
printf("%lld\n",ans);}
