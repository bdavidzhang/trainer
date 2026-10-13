#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
// canonical frame: order-k box, cells [0,W]^2, W=2^k-2, opening facing down.
// returns path (vertex list) from cell (x,y) inside the box to the first cell outside it.
vector<P> path(int k, ll x, ll y){
    ll m = 1LL<<(k-1), W = 2*m-2;
    vector<P> res;
    if(x!=m-1 && y!=m-1){
        ll Wc = m-2;
        vector<P> ch;
        if(y>=m){
            ll ox = x>=m? m:0;
            ch = path(k-1, x-ox, y-m);
            for(auto& p: ch){ p.first+=ox; p.second+=m; }
        } else if(x<m){ // bottom-left, opening left: canonical = (y,x)
            ch = path(k-1, y, x);
            for(auto& p: ch) swap(p.first,p.second);
        } else { // bottom-right, opening right: canonical = (ly, Wc-lx)
            ch = path(k-1, y, Wc-(x-m));
            for(auto& p: ch){ ll cx=p.first, cy=p.second; p.first = Wc-cy+m; p.second = cx; }
        }
        res = ch;
        x = res.back().first; y = res.back().second;
        if(x<0||x>W||y<0||y>W) return res;
    } else res.push_back({x,y});
    if(x==m-1 && y>=m){ res.push_back({m-1,W+1}); return res; }
    if(x!=m-1) res.push_back({m-1,m-1});
    res.push_back({m-1,-1});
    return res;
}
ll plen(const vector<P>& p){ ll s=0; for(size_t i=1;i<p.size();i++) s+=llabs(p[i].first-p[i-1].first)+llabs(p[i].second-p[i-1].second); return s; }
int sg(ll v){return (v>0)-(v<0);}
int main(){
    int T; scanf("%d",&T);
    while(T--){
        int n; ll x1,y1,x2,y2; scanf("%d %lld %lld %lld %lld",&n,&x1,&y1,&x2,&y2);
        ll W=(1LL<<n)-2;
        auto get=[&](ll x,ll y){
            vector<P> p;
            if(x<0||x>W||y<0||y>W) p.push_back({x,y}); else p=path(n,x,y);
            vector<P> q; for(auto& a:p) if(q.empty()||q.back()!=a) q.push_back(a);
            reverse(q.begin(),q.end());
            return q;
        };
        vector<P> A=get(x1,y1), B=get(x2,y2);
        ll la=plen(A), lb=plen(B), ans;
        if(A[0]==B[0]){
            ll common=0; P c=A[0]; size_t i=1,j=1;
            while(i<A.size()&&j<B.size()){
                int ax=sg(A[i].first-c.first), ay=sg(A[i].second-c.second);
                int bx=sg(B[j].first-c.first), by=sg(B[j].second-c.second);
                if(ax!=bx||ay!=by) break;
                ll da=llabs(A[i].first-c.first)+llabs(A[i].second-c.second);
                ll db=llabs(B[j].first-c.first)+llabs(B[j].second-c.second);
                ll s=min(da,db); common+=s; c.first+=ax*s; c.second+=ay*s;
                if(da==s) i++; if(db==s) j++;
            }
            ans=la+lb-2*common;
        } else {
            ll ax=A[0].first, ay=A[0].second, bx=B[0].first, by=B[0].second;
            ll d=llabs(ax-bx)+llabs(ay-by);
            auto in=[&](ll v){return v>=0&&v<=W;};
            if(in(ay)&&in(by)&&((ax<0&&bx>W)||(bx<0&&ax>W))){
                d=llabs(ax-bx)+min((ay+1)+(by+1),(W+1-ay)+(W+1-by));
            } else if(in(ax)&&in(bx)&&((ay<0&&by>W)||(by<0&&ay>W))){
                d=llabs(ay-by)+min((ax+1)+(bx+1),(W+1-ax)+(W+1-bx));
            }
            ans=la+lb+d;
        }
        printf("%lld\n",ans);
    }
}
