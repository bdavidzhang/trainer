#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// floor division
static ll fdiv(ll a, ll b){ ll q=a/b; if((a%b!=0) && ((a<0)!=(b<0))) q--; return q; }
static ll best(ll s, ll c){ return fdiv(2*s+c, 2*c); } // nearest integer to s/c
int main(){
    int n; scanf("%d",&n);
    vector<ll> a(n);
    for(int i=0;i<n;i++){ ll x; scanf("%lld",&x); a[i]=x-i; }
    // isotonic regression (non-decreasing integer y) by pool adjacent violators
    vector<ll> bs, bc, bv;
    bs.reserve(n); bc.reserve(n); bv.reserve(n);
    for(int i=0;i<n;i++){
        ll s=a[i], c=1, v=a[i];
        while(!bs.empty() && bv.back()>v){
            s+=bs.back(); c+=bc.back();
            bs.pop_back(); bc.pop_back(); bv.pop_back();
            v=best(s,c);
        }
        bs.push_back(s); bc.push_back(c); bv.push_back(v);
    }
    unsigned long long ans=0; int idx=0;
    for(size_t b=0;b<bs.size();b++){
        for(ll k=0;k<bc[b];k++,idx++){ ll d=bv[b]-a[idx]; ans+=(unsigned long long)(d*d); }
    }
    printf("%llu\n",ans);
}
