#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n; int k; scanf("%lld %d",&n,&k);
    vector<pair<ll,ll>> v(k); // (end,start)
    for(auto&p:v) scanf("%lld %lld",&p.second,&p.first);
    sort(v.begin(),v.end());
    vector<ll> dp(k+1,0); // best using first i intervals (by end)
    for(int i=0;i<k;i++){
        ll a=v[i].second,b=v[i].first;
        // number of intervals with end < a
        int j=lower_bound(v.begin(),v.end(),make_pair(a,(ll)LLONG_MIN))-v.begin();
        dp[i+1]=max(dp[i],dp[j]+(b-a+1));
    }
    printf("%lld\n",n-dp[k]);
}
