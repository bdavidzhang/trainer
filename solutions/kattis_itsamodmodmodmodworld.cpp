#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// sum_{i=0}^{n} floor((a*i+b)/c)
ll fs(ll a,ll b,ll c,ll n){
    if(n<0) return 0;
    if(a==0) return (b/c)*(n+1);
    if(a>=c||b>=c) return (a/c)*(n*(n+1)/2)+(b/c)*(n+1)+fs(a%c,b%c,c,n);
    ll m=(a*n+b)/c;
    return n*m-fs(c,c-b-1,a,m-1);
}
int main(){
    int W; scanf("%d",&W);
    while(W--){
        ll p,q,n; scanf("%lld %lld %lld",&p,&q,&n);
        ll r=p%q;
        ll ans=r*(n*(n+1)/2)-q*fs(r,0,q,n);
        printf("%lld\n",ans);
    }
}
