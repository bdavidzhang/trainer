#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef pair<ld,ld> P;
static ld cr(const P&o,const P&a,const P&b){return (a.first-o.first)*(b.second-o.second)-(a.second-o.second)*(b.first-o.first);}
int main(){
    int n; ld b; cin>>n>>b;
    vector<P> p(n);
    for(auto&q:p){ld c,h,t;cin>>c>>h>>t;q={h/c,t/c};}
    sort(p.begin(),p.end());p.erase(unique(p.begin(),p.end()),p.end());
    // upper hull (left to right)
    vector<P> h;
    for(auto&q:p){
        while(h.size()>=2&&cr(h[h.size()-2],h.back(),q)>=0)h.pop_back();
        h.push_back(q);
    }
    ld best=0;
    for(auto&q:h)best=max(best,q.first*q.second);
    for(size_t i=0;i+1<h.size();i++){
        ld ax=h[i].first,ay=h[i].second,dx=h[i+1].first-ax,dy=h[i+1].second-ay;
        if(dx*dy<0){
            ld t=-(ax*dy+ay*dx)/(2*dx*dy);
            if(t>0&&t<1)best=max(best,(ax+t*dx)*(ay+t*dy));
        }
    }
    printf("%.4f\n",(double)(best*b*b));
}
