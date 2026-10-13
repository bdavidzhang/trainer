#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m; vector<pair<ll,ll>> a; // (deadline, length)
bool ok(ll v){
    priority_queue<ll> pq; ll sum=0; int late=0;
    for(auto&b:a){
        pq.push(b.second); sum+=b.second;
        if(sum>b.first*v){ sum-=pq.top(); pq.pop(); if(++late>m)return false; }
    }
    return true;
}
int main(){
    scanf("%d %d",&n,&m); a.resize(n);
    for(auto&b:a)scanf("%lld %lld",&b.second,&b.first);
    sort(a.begin(),a.end());
    ll lo=1,hi=200000000000000LL;
    while(lo<hi){ ll mid=(lo+hi)/2; if(ok(mid))hi=mid; else lo=mid+1; }
    printf("%lld\n",lo);
}
