#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){ll n;int k;scanf("%lld %d",&n,&k);
    map<ll,vector<pair<ll,ll>>> rows;
    for(int i=0;i<k;i++){ll x,y,b;scanf("%lld %lld %lld",&x,&y,&b);
        ll w=0;while((w+1)*(w+1)*(w+1)<=b)w++;
        for(ll d=-w;d<=w;d++){ll p=x+d;if(p<0||p>n)continue;
            ll rem=b-llabs(d)*d*d;
            ll h=0;while((h+1)*(h+1)*(h+1)<=rem)h++;
            rows[p].push_back({max(0LL,y-h),min(n,y+h)});}
    }
    ll cov=0;
    for(auto&kv:rows){auto&v=kv.second;sort(v.begin(),v.end());ll cur=-1;
        for(auto&p:v){ll l=max(p.first,cur+1);if(p.second>=l){cov+=p.second-l+1;cur=p.second;}}}
    printf("%lld\n",(n+1)*(n+1)-cov);}
