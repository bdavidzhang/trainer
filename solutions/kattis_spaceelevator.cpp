#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// "Up-main" paths: H0 -> up to x1 -> down to L -> sweep up to R (zigzagging over the
// still-unserved down requests) -> down to E.  Down requests [c,d] (pick at d, drop at c)
// are served by the prefix if d<=x1, by the suffix if c>=E, otherwise by a zigzag.
static ll solve(ll H0, const vector<pair<ll,ll>>&rq){
    ll L=H0,R=H0;
    vector<pair<ll,ll>> dn; vector<ll> cand={H0};
    for(auto&[u,v]:rq){
        L=min({L,u,v}); R=max({R,u,v});
        if(u>v) dn.push_back({v,u});
        cand.push_back(u); cand.push_back(v);
    }
    sort(cand.begin(),cand.end()); cand.erase(unique(cand.begin(),cand.end()),cand.end());
    int K=cand.size(), m=dn.size();
    sort(dn.begin(),dn.end());
    vector<ll> s,e,pre;
    for(auto&[a,b]:dn){
        if(!s.empty()&&a<=e.back()) e.back()=max(e.back(),b);
        else {s.push_back(a);e.push_back(b);}
    }
    pre.assign(s.size()+1,0);
    for(size_t i=0;i<s.size();i++) pre[i+1]=pre[i]+e[i]-s[i];
    auto mD=[&](ll x)->ll{
        size_t k=upper_bound(s.begin(),s.end(),x)-s.begin();
        if(k==0) return 0;
        return pre[k-1]+min(x,e[k-1])-s[k-1];
    };
    // lo(x): min c over intervals with c<=x<d
    vector<ll> lo(K),hi(K);
    {
        priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq; int p=0;
        for(int i=0;i<K;i++){
            ll x=cand[i];
            while(p<m&&dn[p].first<=x){pq.push(dn[p]);p++;}
            while(!pq.empty()&&pq.top().second<=x) pq.pop();
            lo[i]=pq.empty()?x:pq.top().first;
        }
    }
    vector<pair<ll,ll>> byd(m); for(int i=0;i<m;i++) byd[i]={dn[i].second,dn[i].first};
    sort(byd.begin(),byd.end());
    {   // hi(x): max d over intervals with c<x<=d
        priority_queue<pair<ll,ll>> pq; int p=m-1;
        for(int i=K-1;i>=0;i--){
            ll x=cand[i];
            while(p>=0&&byd[p].first>=x){pq.push(byd[p]);p--;}
            while(!pq.empty()&&pq.top().second>=x) pq.pop();
            hi[i]=pq.empty()?x:pq.top().first;
        }
    }
    // sufmin[i] = min c over byd[i..]
    vector<ll> suf(m+1,LLONG_MAX); for(int i=m-1;i>=0;i--) suf[i]=min(suf[i+1],byd[i].second);
    ll best=LLONG_MAX, bestA=LLONG_MAX;
    for(int i=0;i<K;i++){
        ll x=cand[i];
        // as E, with some x1<E
        if(bestA!=LLONG_MAX){
            ll B=-x+2*mD(x)+2*(hi[i]-x);
            best=min(best,bestA+B);
        }
        if(x>=H0){
            // case E<=x1
            int k=upper_bound(byd.begin(),byd.end(),make_pair(x,LLONG_MAX))-byd.begin(); // d>x
            ll E=min(x,suf[k]);
            best=min(best,2*x-E);
            ll A=2*x-2*mD(x)+2*(x-lo[i]);
            bestA=min(bestA,A);
        }
    }
    return best+2*R-2*L-H0;
}
int main(){
    int n; ll H0; scanf("%d %lld",&n,&H0);
    vector<pair<ll,ll>> rq(n); for(auto&[u,v]:rq) scanf("%lld %lld",&u,&v);
    ll a=solve(H0,rq);
    for(auto&[u,v]:rq){u=-u;v=-v;}
    ll b=solve(-H0,rq);
    printf("%lld\n",min(a,b));
}
