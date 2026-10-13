#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Ev{ ll dx,dy,c,pos; int w;
    bool operator<(const Ev&o)const{
        if(dx!=o.dx) return dx<o.dx;
        if(dy!=o.dy) return dy<o.dy;
        if(c!=o.c) return c<o.c;
        return pos<o.pos;
    }
};
vector<Ev> ev;
void addEdge(ll ax,ll ay,ll bx,ll by,int s){
    ll dx=bx-ax, dy=by-ay;
    ll g=std::gcd(llabs(dx),llabs(dy));
    dx/=g; dy/=g;
    if(dx<0||(dx==0&&dy<0)){ dx=-dx; dy=-dy; s=-s; swap(ax,bx); swap(ay,by); }
    ll c=dx*ay-dy*ax;
    ll p1= dx!=0? ax:ay, p2= dx!=0? bx:by;
    ev.push_back({dx,dy,c,p1,s});
    ev.push_back({dx,dy,c,p2,-s});
}
int main(){
    for(int s=1;s>=-1;s-=2){
        int n; if(scanf("%d",&n)!=1) n=0;
        for(int i=0;i<n;i++){
            ll x[3],y[3];
            for(int j=0;j<3;j++) scanf("%lld %lld",&x[j],&y[j]);
            __int128 cr=(__int128)(x[1]-x[0])*(y[2]-y[0])-(__int128)(y[1]-y[0])*(x[2]-x[0]);
            if(cr<0){ swap(x[1],x[2]); swap(y[1],y[2]); }
            for(int j=0;j<3;j++){ int k=(j+1)%3; addEdge(x[j],y[j],x[k],y[k],s); }
        }
    }
    sort(ev.begin(),ev.end());
    size_t i=0; bool same=true;
    while(i<ev.size()){
        size_t j=i; ll sum=0;
        while(j<ev.size()&&ev[j].dx==ev[i].dx&&ev[j].dy==ev[i].dy&&ev[j].c==ev[i].c&&ev[j].pos==ev[i].pos){ sum+=ev[j].w; j++; }
        if(sum!=0){ same=false; break; }
        i=j;
    }
    puts(same?"yes":"no");
}
