#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static vector<ll> gen(const vector<ll>&a){
    vector<ll> cur={0},nx;
    for(ll x:a){
        nx.resize(cur.size()*2);
        size_t i=0,j=0,k=0,n=cur.size();
        while(i<n||j<n){
            if(j>=n||(i<n&&cur[i]<=cur[j]+x)) nx[k++]=cur[i++]; else nx[k++]=cur[j++]+x;
        }
        cur.swap(nx);
    }
    return cur;
}
int main(){
    int n; scanf("%d",&n); vector<ll> a(n); ll S=0; for(auto&x:a){scanf("%lld",&x);S+=x;}
    vector<ll> A=gen(vector<ll>(a.begin(),a.begin()+n/2)), B=gen(vector<ll>(a.begin()+n/2,a.end()));
    auto cnt=[&](ll x)->ll{ // pairs with sum<=x
        if(x<0) return 0;
        ll c=0; long j=(long)B.size()-1;
        for(size_t i=0;i<A.size();i++){
            while(j>=0&&A[i]+B[j]>x) j--;
            if(j<0) break;
            c+=j+1;
        }
        return c;
    };
    ll lo=0,hi=S; ll base=0; // base = cnt(lo-1)
    while(lo<hi){
        ll mid=lo+(hi-lo)/2;
        ll c=cnt(mid)-base;
        if(c>mid-lo+1) hi=mid; else { lo=mid+1; base+=c; }
    }
    printf("%lld\n",lo);
}
