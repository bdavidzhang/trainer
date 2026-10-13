#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct P{ll x,y;};
static ll cr(P a,P b,P c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}
static int sg(ll v){return v>0?1:(v<0?-1:0);}
static ll rd(){double v;scanf("%lf",&v);return llround(v*10000.0);}
int n;
vector<P> A,B;
vector<vector<pair<double,int>>> on; // per walkway: (param, node)
vector<vector<pair<int,double>>> g;
// do non-parallel segments ab, cd intersect?
static bool inter(P a,P b,P c,P d){
    ll den=(b.x-a.x)*(d.y-c.y)-(b.y-a.y)*(d.x-c.x);
    if(den==0) return false;
    if(sg(cr(a,b,c))*sg(cr(a,b,d))>0) return false;
    if(sg(cr(c,d,a))*sg(cr(c,d,b))>0) return false;
    return true;
}
// parameter along ab of intersection with line cd
static double par(P a,P b,P c,P d){
    double den=(double)(b.x-a.x)*(double)(d.y-c.y)-(double)(b.y-a.y)*(double)(d.x-c.x);
    double num=(double)(c.x-a.x)*(double)(d.y-c.y)-(double)(c.y-a.y)*(double)(d.x-c.x);
    return num/den;
}
static bool onSeg(P a,P b,P p){
    if(cr(a,b,p)!=0) return false;
    return min(a.x,b.x)<=p.x&&p.x<=max(a.x,b.x)&&min(a.y,b.y)<=p.y&&p.y<=max(a.y,b.y);
}
static double ptPar(P a,P b,P p){
    double dx=b.x-a.x,dy=b.y-a.y;
    double l=dx*dx+dy*dy;
    if(l==0) return 0;
    return ((p.x-a.x)*dx+(p.y-a.y)*dy)/l;
}
int main(){
    scanf("%d",&n);
    A.resize(n);B.resize(n);
    for(int i=0;i<n;i++){ll a,b,c,d;scanf("%lld %lld %lld %lld",&a,&b,&c,&d);A[i]={a*10000,b*10000};B[i]={c*10000,d*10000};}
    P S;S.x=rd();S.y=rd();double vs;scanf("%lf",&vs);
    P F1,F2;F1.x=rd();F1.y=rd();F2.x=rd();F2.y=rd();double vf;scanf("%lf",&vf);
    on.assign(n,{});
    int cnt=0;
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
        if(inter(A[i],B[i],A[j],B[j])){
            int id=cnt++;
            on[i].push_back({par(A[i],B[i],A[j],B[j]),id});
            on[j].push_back({par(A[j],B[j],A[i],B[i]),id});
        }
    }
    int sid=cnt++;
    for(int i=0;i<n;i++) if(onSeg(A[i],B[i],S)) on[i].push_back({ptPar(A[i],B[i],S),sid});
    vector<pair<int,double>> meets; // node, fellow distance
    double flen=hypot((double)(F2.x-F1.x),(double)(F2.y-F1.y));
    for(int i=0;i<n;i++){
        if(F1.x==F2.x&&F1.y==F2.y){
            if(onSeg(A[i],B[i],F1)){int id=cnt++;on[i].push_back({ptPar(A[i],B[i],F1),id});meets.push_back({id,0.0});}
        } else if(A[i].x==B[i].x&&A[i].y==B[i].y){
            if(onSeg(F1,F2,A[i])){int id=cnt++;on[i].push_back({0.0,id});meets.push_back({id,ptPar(F1,F2,A[i])*flen});}
        } else if(inter(A[i],B[i],F1,F2)){
            int id=cnt++;
            on[i].push_back({par(A[i],B[i],F1,F2),id});
            double t=par(F1,F2,A[i],B[i]);
            t=min(1.0,max(0.0,t));
            meets.push_back({id,t*flen});
        }
    }
    g.assign(cnt,{});
    for(int i=0;i<n;i++){
        auto&v=on[i];
        sort(v.begin(),v.end());
        double len=hypot((double)(B[i].x-A[i].x),(double)(B[i].y-A[i].y));
        for(size_t k=1;k<v.size();k++){
            double w=(v[k].first-v[k-1].first)*len;
            if(w<0)w=0;
            g[v[k].second].push_back({v[k-1].second,w});
            g[v[k-1].second].push_back({v[k].second,w});
        }
    }
    vector<double> dist(cnt,1e300);
    priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> pq;
    dist[sid]=0;pq.push({0,sid});
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop();
        if(d>dist[u])continue;
        for(auto&e:g[u]) if(d+e.second<dist[e.first]){dist[e.first]=d+e.second;pq.push({dist[e.first],e.first});}
    }
    double best=1e300;
    for(auto&m:meets){
        if(dist[m.first]>1e299)continue;
        double ts=dist[m.first]/1e4/vs, tf=m.second/1e4/vf;
        if(ts<=tf+1e-9*max(1.0,tf)) best=min(best,tf);
    }
    if(best>1e299)puts("Impossible");else printf("%.9f\n",best);
}
