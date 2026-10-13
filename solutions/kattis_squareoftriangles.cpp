#include <bits/stdc++.h>
using namespace std;
typedef long double D;
const D EPS=1e-10L;
const D PI=acosl(-1.0L);
struct P{D x,y;};
struct Tri{P v[3];};
D len[4][3], ang[4][3];
bool usedT[4];
vector<Tri> placed;
static D cross(P a,P b,P c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}
static D norm2pi(D a){ a=fmodl(a,2*PI); if(a<0) a+=2*PI; if(a>2*PI-EPS) a=0; return a; }
static D ccw(D a,D b){ return norm2pi(b-a); }
static bool same(P a,P b){return fabsl(a.x-b.x)<EPS&&fabsl(a.y-b.y)<EPS;}
// is there a separating edge line of A against B
static bool sepBy(const Tri&A,const Tri&B){
    for(int i=0;i<3;i++){
        P a=A.v[i],b=A.v[(i+1)%3];
        D l=hypotl(b.x-a.x,b.y-a.y);
        bool all=true;
        for(int j=0;j<3;j++) if(cross(a,b,B.v[j])>EPS*l){all=false;break;}
        if(all) return true;
    }
    return false;
}
static bool overlap(const Tri&A,const Tri&B){ return !(sepBy(A,B)||sepBy(B,A)); }
bool findAnchor(P&V,D&e,D&gap){
    vector<P> cands={{0,0},{1,0},{1,1},{0,1}};
    for(auto&t:placed) for(int i=0;i<3;i++) cands.push_back(t.v[i]);
    for(P c:cands){
        vector<pair<D,D>> iv;
        if(fabsl(c.x)<EPS) iv.push_back({PI/2,PI});
        if(fabsl(c.x-1)<EPS) iv.push_back({3*PI/2,PI});
        if(fabsl(c.y)<EPS) iv.push_back({PI,PI});
        if(fabsl(c.y-1)<EPS) iv.push_back({0,PI});
        for(auto&t:placed){
            bool isV=false;
            for(int i=0;i<3;i++) if(same(c,t.v[i])){
                P a=t.v[(i+1)%3],b=t.v[(i+2)%3];
                D s=atan2l(a.y-c.y,a.x-c.x), f=atan2l(b.y-c.y,b.x-c.x);
                iv.push_back({norm2pi(s),ccw(s,f)}); isV=true; break;
            }
            if(isV) continue;
            for(int i=0;i<3;i++){
                P a=t.v[i],b=t.v[(i+1)%3];
                D l=hypotl(b.x-a.x,b.y-a.y);
                if(fabsl(cross(a,b,c))<EPS*l){
                    D dt=((c.x-a.x)*(b.x-a.x)+(c.y-a.y)*(b.y-a.y))/l;
                    if(dt>EPS&&dt<l-EPS){ iv.push_back({norm2pi(atan2l(b.y-a.y,b.x-a.x)),PI}); break; }
                }
            }
        }
        if(iv.empty()) continue;
        for(auto&I:iv){
            D en=norm2pi(I.first+I.second);
            bool cov=false;
            for(auto&J:iv){ D d=ccw(J.first,en); if(d<J.second-EPS){cov=true;break;} }
            if(cov) continue;
            D g=2*PI;
            for(auto&J:iv){ D d=ccw(en,J.first); if(d<EPS) d=2*PI; g=min(g,d); }
            if(g>EPS&&g<PI-EPS){ V=c;e=en;gap=g;return true; }
        }
    }
    return false;
}
bool rec(int cnt){
    if(cnt==4) return true;
    P V;D e,gap;
    if(!findAnchor(V,e,gap)) return false;
    for(int t=0;t<4;t++) if(!usedT[t]){
        // skip identical triangles already tried at this level
        bool dup=false;
        for(int u=0;u<t;u++) if(!usedT[u]){
            D a1[3],a2[3]; for(int i=0;i<3;i++){a1[i]=len[t][i];a2[i]=len[u][i];}
            sort(a1,a1+3);sort(a2,a2+3);
            if(a1[0]==a2[0]&&a1[1]==a2[1]&&a1[2]==a2[2]) dup=true;
        }
        if(dup) continue;
        for(int c=0;c<3;c++){
            D al=ang[t][c];
            if(al>gap+EPS) continue;
            D p=len[t][(c+1)%3],q=len[t][(c+2)%3];
            for(int o=0;o<2;o++){
                if(o) swap(p,q);
                Tri T; T.v[0]=V; T.v[1]={V.x+p*cosl(e),V.y+p*sinl(e)}; T.v[2]={V.x+q*cosl(e+al),V.y+q*sinl(e+al)};
                bool ok=true;
                for(int i=1;i<3&&ok;i++) if(T.v[i].x<-EPS||T.v[i].x>1+EPS||T.v[i].y<-EPS||T.v[i].y>1+EPS) ok=false;
                for(size_t i=0;i<placed.size()&&ok;i++) if(overlap(placed[i],T)) ok=false;
                if(!ok) continue;
                usedT[t]=true; placed.push_back(T);
                bool r=rec(cnt+1);
                placed.pop_back(); usedT[t]=false;
                if(r) return true;
            }
        }
    }
    return false;
}
int main(){
    int T; scanf("%d",&T);
    while(T--){
        long long sq[4][3]; D area4[4]; D tot=0;
        for(int i=0;i<4;i++){
            long long a,b,c; scanf("%lld %lld %lld",&a,&b,&c); sq[i][0]=a;sq[i][1]=b;sq[i][2]=c;
            long long s16=2*(a*b+b*c+c*a)-(a*a+b*b+c*c);
            area4[i]=sqrtl((D)s16); tot+=area4[i]/4;
        }
        D s=sqrtl(tot);
        for(int i=0;i<4;i++) for(int c=0;c<3;c++){
            len[i][c]=sqrtl((D)sq[i][c])/s;
            // corner c opposite side c
            long long p2=sq[i][(c+1)%3],q2=sq[i][(c+2)%3],r2=sq[i][c];
            ang[i][c]=atan2l(area4[i],(D)(p2+q2-r2));
        }
        placed.clear(); for(int i=0;i<4;i++) usedT[i]=false;
        puts(rec(0)?"1":"0");
    }
}
