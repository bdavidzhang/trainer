#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct R{ll x1,y1,x2,y2;};
vector<R> rs;
bool ok=true;
// side of rect r w.r.t. line through (px,py) dir (dx,dy): +1 left(closed), -1 right(closed), 0 straddles
static inline int side(const R&r,ll px,ll py,ll dx,ll dy){
    // cross = dx*(y-py) - dy*(x-px); maximise / minimise over corners
    ll ymax = dx>=0? r.y2:r.y1, ymin = dx>=0? r.y1:r.y2;
    ll xmin_ = dy>=0? r.x1:r.x2, xmax_ = dy>=0? r.x2:r.x1;
    ll mx = dx*(ymax-py) - dy*(xmin_-px);
    ll mn = dx*(ymin-py) - dy*(xmax_-px);
    if(mn>=0) return 1;
    if(mx<=0) return -1;
    return 0;
}
void rec(vector<int> ids){
    if(!ok||ids.size()<=1)return;
    int m=ids.size();
    vector<array<ll,2>> pts; vector<int> own;
    for(int id:ids){
        const R&r=rs[id];
        pts.push_back({r.x1,r.y1});pts.push_back({r.x1,r.y2});pts.push_back({r.x2,r.y1});pts.push_back({r.x2,r.y2});
        for(int t=0;t<4;t++)own.push_back(id);
    }
    int P=pts.size();
    for(int i=0;i<P;i++)for(int j=i+1;j<P;j++){
        ll dx=pts[j][0]-pts[i][0],dy=pts[j][1]-pts[i][1];
        if(dx==0&&dy==0)continue;
        int pos=0,neg=0;bool bad=false;
        for(int t=0;t<m;t++){
            int s=side(rs[ids[t]],pts[i][0],pts[i][1],dx,dy);
            if(s==0){bad=true;break;}
            if(s>0)pos++;else neg++;
        }
        if(bad||!pos||!neg)continue;
        vector<int> a,b;
        for(int t=0;t<m;t++){
            if(side(rs[ids[t]],pts[i][0],pts[i][1],dx,dy)>0)a.push_back(ids[t]);else b.push_back(ids[t]);
        }
        rec(a);rec(b);
        return;
    }
    ok=false;
}
int main(){
    int n;scanf("%d",&n);
    rs.resize(n);
    for(auto&r:rs)scanf("%lld %lld %lld %lld",&r.x1,&r.y1,&r.x2,&r.y2);
    vector<int> ids(n);iota(ids.begin(),ids.end(),0);
    rec(ids);
    if(ok)printf("%d\n",n-1);else puts("impossible");
}
