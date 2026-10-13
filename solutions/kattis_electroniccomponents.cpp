#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;
// Sort types by time descending. Let k_i = number of still-unpaired ("open") larger components before type i.
// x_i = (k_i + f_i - k_{i+1})/2 components of type i are paired with open ones (saving t_i each).
// Feasible iff |k_i - f_i| <= k_{i+1} <= k_i + f_i (triangle inequality), k_1 = 0.
// cost = (sum f_i t_i + sum_{i>=2} (t_{i-1}-t_i) k_i + t_n k_{n+1}) / 2  -> minimise a convex chain.
// g_i(k) is convex piecewise linear on the parity lattice; keep it as a breakpoint list.
vector<pair<ll,ll>> pts; // (k, value), sorted by k
static ll evalg(ll x){
    int lo=0, hi=(int)pts.size()-1;
    if(x<=pts[0].first) return pts[0].second;
    if(x>=pts[hi].first) return pts[hi].second;
    while(hi-lo>1){ int mid=(lo+hi)/2; if(pts[mid].first<=x) lo=mid; else hi=mid; }
    ll x0=pts[lo].first,y0=pts[lo].second,x1=pts[hi].first,y1=pts[hi].second;
    if(x==x0) return y0;
    return (ll)(y0 + (lll)(y1-y0)*(x-x0)/(x1-x0));
}
int main(){
    int n; if(scanf("%d",&n)!=1) return 0;
    vector<pair<ll,ll>> a(n); // (t,f)
    ll total=0;
    for(auto&p:a){ scanf("%lld %lld",&p.second,&p.first); total+=p.first*p.second; }
    sort(a.begin(),a.end(),greater<pair<ll,ll>>());
    ll M=0; for(auto&p:a) M=max(M,p.second);
    // Clipping k_i to min(k_i, M or M+1 (matching parity)) keeps feasibility and never increases cost,
    // so the domain can be capped at M+1 and the breakpoint list stays small.
    pts.push_back({0,0});
    for(int i=0;i<n;i++){
        ll f=a[i].second;
        ll c=(i+1<n)? a[i].first-a[i+1].first : a[i].first;
        ll L=pts.front().first, R=pts.back().first;
        // minimiser
        int mi=0; for(int j=1;j<(int)pts.size();j++) if(pts[j].second<pts[mi].second) mi=j;
        ll m=pts[mi].first;
        ll lo=max({L-f, f-R, (ll)((L+f)&1)}), hi=R+f;
        ll cap=M; if((cap&1)!=((L+f)&1)) cap++;
        hi=min(hi,cap);
        vector<ll> cand; cand.reserve(pts.size()*3+4);
        for(auto&p:pts){ cand.push_back(p.first+f); cand.push_back(p.first-f); cand.push_back(f-p.first); }
        cand.push_back(llabs(m-f)); cand.push_back(m+f); cand.push_back(lo); cand.push_back(hi);
        sort(cand.begin(),cand.end()); cand.erase(unique(cand.begin(),cand.end()),cand.end());
        vector<pair<ll,ll>> np;
        for(ll k:cand){
            if(k<lo||k>hi) continue;
            ll wl=llabs(k-f), wr=k+f;
            ll arg=min(max(m,wl),wr);
            ll v=evalg(arg)+c*k;
            // drop collinear middle points
            while(np.size()>=2){
                auto&p1=np[np.size()-2]; auto&p2=np[np.size()-1];
                if((lll)(p2.second-p1.second)*(k-p2.first)==(lll)(v-p2.second)*(p2.first-p1.first)) np.pop_back(); else break;
            }
            np.push_back({k,v});
        }
        pts.swap(np);
    }
    ll best=LLONG_MAX; for(auto&p:pts) best=min(best,p.second);
    printf("%lld\n",(total+best)/2);
}
