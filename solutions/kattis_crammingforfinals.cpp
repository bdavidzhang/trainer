#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll r,c; int d,n; scanf("%lld %lld %d %d",&r,&c,&d,&n);
    vector<pair<ll,ll>> s(n);
    for(auto&p:s)scanf("%lld %lld",&p.first,&p.second);
    sort(s.begin(),s.end());
    vector<int> w(d+1);
    for(int dy=0;dy<=d;dy++){
        ll q=(ll)d*d-(ll)dy*dy; ll x=(ll)sqrtl((long double)q);
        while(x*x>q)x--; while((x+1)*(x+1)<=q)x++;
        w[dy]=(int)x;
    }
    // rows covered by nobody?
    ll covered=0, curEnd=0;
    vector<pair<ll,ll>> iv;
    for(auto&p:s){
        ll a=max(1LL,p.first-d), b=min(r,p.first+d);
        if(!iv.empty() && a<=iv.back().second+1) iv.back().second=max(iv.back().second,b);
        else iv.push_back({a,b});
    }
    for(auto&v:iv)covered+=v.second-v.first+1;
    (void)curEnd;
    if(covered<r){puts("0");return 0;}
    int best=INT_MAX;
    const int INF=1000000;
    int lo=0,hi=0; // active students s[lo..hi)
    vector<pair<ll,int>> ev;
    for(auto&v:iv){
        for(ll row=v.first;row<=v.second;row++){
            while(hi<n && s[hi].first<=row+d)hi++;
            while(lo<hi && s[lo].first<row-d)lo++;
            ev.clear();
            ev.push_back({1,0});
            for(int k=lo;k<hi;k++){
                int dy=(int)llabs(s[k].first-row);
                ll L=max(1LL,s[k].second-w[dy]), R=min(c,s[k].second+w[dy]);
                ev.push_back({L,1});ev.push_back({R+1,-1});
                if(dy==0){ev.push_back({s[k].second,INF});ev.push_back({s[k].second+1,-INF});}
            }
            sort(ev.begin(),ev.end());
            int cur=0; size_t i=0;
            while(i<ev.size()){
                ll pos=ev[i].first;
                while(i<ev.size()&&ev[i].first==pos){cur+=ev[i].second;i++;}
                if(pos<=c) best=min(best,cur);
            }
            if(best==0){puts("0");return 0;}
        }
    }
    printf("%d\n",best);
}
