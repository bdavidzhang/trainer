#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,k;scanf("%d %d",&n,&k);vector<ll> w(n),h(n),q(n);
    for(int i=0;i<n;i++)scanf("%lld %lld %lld",&w[i],&h[i],&q[i]);
    int F=1<<n;vector<ll> cost(F,0);
    for(int m=1;m<F;m++){ll mw=0,mh=0,sq=0,sa=0;for(int i=0;i<n;i++)if(m>>i&1){mw=max(mw,w[i]);mh=max(mh,h[i]);sq+=q[i];sa+=w[i]*h[i]*q[i];}cost[m]=mw*mh*sq-sa;}
    k=min(k,n);
    vector<ll> dp(cost),nd(F);
    for(int it=2;it<=k;it++){
        nd=dp;
        for(int m=1;m<F;m++){
            int low=m&-m,rest=m^low;ll b=nd[m];
            for(int s=rest;;s=(s-1)&rest){ // group = low|s, remaining = rest^s
                int rem=rest^s;
                if(rem){ll c=cost[low|s]+dp[rem];if(c<b)b=c;}
                if(!s)break;
            }
            nd[m]=b;
        }
        dp.swap(nd);
    }
    printf("%lld\n",dp[F-1]);
}
