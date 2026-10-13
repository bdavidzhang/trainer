#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n; ll c;
vector<ll> t,d;
ll sumT;
bool feasible(ll R){
    // free research units: at most R per task, R*c in total; one extra unit per task in the last attempt costs 1 second
    __int128 K=(__int128)R*c;
    vector<pair<ll,ll>> items; items.reserve(2*n); // (gain, count), cap R per task
    ll paid=0; // net gain of paid (final attempt) units
    for(int i=0;i<n;i++){
        ll q=t[i]/d[i], r=t[i]%d[i];
        ll full=min(q,R);
        if(full>0) items.push_back({d[i],full});
        if(q<R){ if(r>0) items.push_back({r,1}); }
        else { ll e=(q>R)?d[i]:r; if(e>=2) paid+=e-1; }
    }
    sort(items.begin(),items.end(),greater<pair<ll,ll>>());
    ll gain=0;
    for(auto&it:items){
        ll take=(K>=it.second)?it.second:(ll)K;
        K-=take; gain+=take*it.first;
        ll rest=it.second-take;
        if(rest>0&&it.first>=2) paid+=rest*(it.first-1);
    }
    return sumT-gain-paid<=c;
}
int main(){
    scanf("%d %lld",&n,&c);
    t.resize(n);d.resize(n);
    ll units=0;
    for(int i=0;i<n;i++){scanf("%lld %lld",&t[i],&d[i]);sumT+=t[i];units+=(t[i]+d[i]-1)/d[i];}
    ll lo=0,hi=units;
    while(lo<hi){ ll mid=lo+(hi-lo)/2; if(feasible(mid))hi=mid; else lo=mid+1; }
    printf("%lld\n",lo);
}
