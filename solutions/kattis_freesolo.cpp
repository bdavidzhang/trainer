#include <bits/stdc++.h>
using namespace std;
typedef double D;
struct P{D x,y;};
int main(){
    int n;scanf("%d",&n);
    vector<P> h;
    h.push_back({-0.2,0});h.push_back({0,0});h.push_back({0.2,0});
    P T{0,0};
    for(int i=0;i<n;i++){D x,y;scanf("%lf %lf",&x,&y);if(i==n-1)T={x,y};else h.push_back({x,y});}
    int m=h.size(); // non-target holds
    const D R=1+1e-7;
    auto depth=[&](P p){int c=0;for(int i=0;i<m;i++){if(hypot(p.x-h[i].x,p.y-h[i].y)<=R)c++;}return c;};
    P S{0,0};
    if(hypot(T.x,T.y)<=1+1e-9){printf("0.0000000000\n");return 0;}
    vector<P> nodes;nodes.push_back(S);
    vector<P> cs=h;cs.push_back(T);
    int c=cs.size();
    for(int i=0;i<c;i++)for(int j=i+1;j<c;j++){
        D dx=cs[j].x-cs[i].x,dy=cs[j].y-cs[i].y;D d=hypot(dx,dy);
        if(d>=2||d<1e-12)continue;
        D hh=sqrt(max(0.0,1-d*d/4));
        D mx=(cs[i].x+cs[j].x)/2,my=(cs[i].y+cs[j].y)/2;
        D ux=-dy/d,uy=dx/d;
        for(int s=-1;s<=1;s+=2){
            P p{mx+s*hh*ux,my+s*hh*uy};
            if(depth(p)>=3)nodes.push_back(p);
        }
    }
    int N=nodes.size();
    // segment feasibility
    auto feas=[&](P a,P b)->bool{
        D dx=b.x-a.x,dy=b.y-a.y;D L2=dx*dx+dy*dy;
        if(L2<1e-18)return true;
        static pair<D,int> ev[200];int ne=0;int dep=0;
        for(int i=0;i<m;i++){
            D fx=a.x-h[i].x,fy=a.y-h[i].y;
            D B=fx*dx+fy*dy,C=fx*fx+fy*fy-R*R;
            D disc=B*B-L2*C;
            if(disc<0)continue;
            D sq=sqrt(disc);
            D lo=(-B-sq)/L2,hi=(-B+sq)/L2;
            if(hi<0||lo>1)continue;
            if(lo<=0)dep++;else ev[ne++]={lo,0};
            if(hi<1)ev[ne++]={hi,1};
        }
        if(dep<3)return false;
        sort(ev,ev+ne);
        for(int i=0;i<ne;i++){
            if(ev[i].second==0)dep++;
            else{
                dep--;
                if(dep<3){
                    // allow starts at the same t
                    int k=i+1,dd=dep;
                    while(k<ne&&ev[k].first<=ev[i].first+1e-12){if(ev[k].second==0)dd++;k++;}
                    if(dd<3)return false;
                }
            }
        }
        return true;
    };
    vector<D> dist(N,1e18);vector<char> done(N,0);
    dist[0]=0;
    D best=1e18;
    for(int itx=0;itx<N;itx++){
        int u=-1;
        for(int i=0;i<N;i++)if(!done[i]&&(u<0||dist[i]<dist[u]))u=i;
        if(u<0||dist[u]>=1e17)break;
        done[u]=1;
        if(dist[u]>=best)break;
        P p=nodes[u];
        D dt=hypot(p.x-T.x,p.y-T.y);
        if(dt<=1+1e-9){best=min(best,dist[u]);}
        else if(dist[u]+dt-1<best){
            P q{T.x+(p.x-T.x)/dt,T.y+(p.y-T.y)/dt};
            if(feas(p,q))best=min(best,dist[u]+dt-1);
        }
        for(int v=0;v<N;v++)if(!done[v]){
            D w=hypot(p.x-nodes[v].x,p.y-nodes[v].y);
            if(dist[u]+w<dist[v]&&feas(p,nodes[v]))dist[v]=dist[u]+w;
        }
    }
    if(best>=1e17)printf("-1\n");else printf("%.10f\n",best);
}
