#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n; ll l,r; scanf("%d %lld %lld",&n,&l,&r);
        vector<ll> a(n); for(auto&x:a) scanf("%lld",&x);
        sort(a.begin(),a.end());
        ll zero=0;
        for(int i=0,j=n-1;i<j;i++,j--) zero+=a[j]-a[i];
        ll best=zero;
        {
            ll lt=0,eq=0,gt=0,s=0;
            for(ll x:a){ if(x<l)lt++; else if(x==l)eq++; else gt++; s+=llabs(x-l);}
            if(lt+eq>=gt) best=max(best,s);
        }
        {
            ll lt=0,eq=0,gt=0,s=0;
            for(ll x:a){ if(x<r)lt++; else if(x==r)eq++; else gt++; s+=llabs(x-r);}
            if(gt+eq>=lt) best=max(best,s);
        }
        printf("%lld\n",best);
    }
}
