#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static char buf[1<<25];
size_t bl=0,bp=0;
inline int gc(){ if(bp==bl){ bl=fread(buf,1,sizeof(buf),stdin); bp=0; if(bl==0) return -1;} return buf[bp++]; }
inline ll rd(){ int c=gc(); while(c!='-'&&(c<'0'||c>'9')) c=gc(); int s=1; if(c=='-'){s=-1;c=gc();} ll x=0; while(c>='0'&&c<='9'){x=x*10+(c-'0');c=gc();} return x*s; }
struct P{ ll x,y; };
static inline ll cross(const P&a,const P&b,const P&c){ return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x); }
int main(){
    P s,t; s.x=rd(); s.y=rd(); t.x=rd(); t.y=rd();
    int n=rd();
    vector<P> d(2*(size_t)n+8);
    vector<P> out; out.reserve(n+2);
    int apex=n+3, L=apex, R=apex;
    d[apex]=s; out.push_back(s);
    auto addUp=[&](const P&u){
        while(R>apex && cross(d[R-1],d[R],u)<=0) R--;
        if(R==apex){
            while(apex>L && cross(d[apex],d[apex-1],u)<0){ apex--; R=apex; out.push_back(d[apex]); }
        }
        d[++R]=u;
    };
    auto addLo=[&](const P&l){
        while(L<apex && cross(d[L+1],d[L],l)>=0) L++;
        if(L==apex){
            while(apex<R && cross(d[apex],d[apex+1],l)>0){ apex++; L=apex; out.push_back(d[apex]); }
        }
        d[--L]=l;
    };
    for(int i=0;i<n;i++){
        ll x=rd(), y1=rd(), y2=rd();
        addUp(P{x,y2}); addLo(P{x,y1});
    }
    addUp(t);
    for(int i=apex+1;i<=R;i++) out.push_back(d[i]);
    string o; o.reserve(out.size()*24);
    for(auto&p:out){ o+=to_string(p.x); o+=' '; o+=to_string(p.y); o+='\n'; }
    fwrite(o.data(),1,o.size(),stdout);
}
