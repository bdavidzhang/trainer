#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;scanf("%d",&n);vector<ll>dp(n+2,-1),nd;dp[0]=0;ll prev=0;
for(int i=0;i<n;i++){ll s,p,e,a;scanf("%lld %lld %lld %lld",&s,&p,&e,&a);nd.assign(n+2,-1);
 for(int j=0;j<=i;j++)if(dp[j]>=0){ll f=dp[j]+s-prev;nd[j]=max(nd[j],f);if(f>=a)nd[j+1]=max(nd[j+1],f-a+e-p);}
 dp=nd;prev=e;}
int r=0;for(int j=0;j<=n;j++)if(dp[j]>=0)r=j;printf("%d\n",r);}
