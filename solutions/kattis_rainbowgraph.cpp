#include <bits/stdc++.h>
using namespace std;
int n,m; int ea[105],eb[105],ew[105]; char ec[105];
bool inS[105]; int dsu[105];
int fnd(int x){ while(dsu[x]!=x){ dsu[x]=dsu[dsu[x]]; x=dsu[x];} return x; }
bool member(int t,int e){ return ec[e]=='G' || (t==0?ec[e]=='R':ec[e]=='B'); }
// is (S - x + y) independent in matroid t, i.e. remaining edges of matroid t's graph connect everything
bool check(int t,int x,int y){
    for(int i=1;i<=n;i++) dsu[i]=i; int comp=n;
    for(int e=0;e<m;e++){
        if(!member(t,e)) continue;
        bool removed=(inS[e]&&e!=x)||e==y;
        if(removed) continue;
        int a=fnd(ea[e]),b=fnd(eb[e]); if(a!=b){ dsu[a]=b; comp--; }
    }
    return comp==1;
}
int main(){
    scanf("%d %d",&n,&m); long long total=0;
    for(int i=0;i<m;i++){ scanf("%d %d %d %c",&ea[i],&eb[i],&ew[i],&ec[i]); total+=ew[i]; }
    vector<long long> ans(m+1,-1);
    if(check(0,-1,-1)&&check(1,-1,-1)){
        long long removedW=0; int sz=0; ans[m]=total;
        while(true){
            vector<char> src(m,0),snk(m,0);
            static bool g[105][105];
            for(int i=0;i<m;i++) for(int j=0;j<m;j++) g[i][j]=false;
            for(int y=0;y<m;y++) if(!inS[y]){
                src[y]=!member(0,y)||check(0,-1,y);
                snk[y]=!member(1,y)||check(1,-1,y);
                for(int x=0;x<m;x++) if(inS[x]){
                    if(src[y]||(member(0,x)&&check(0,x,y))) g[x][y]=true;
                    if(snk[y]||(member(1,x)&&check(1,x,y))) g[y][x]=true;
                }
            }
            const long long INF=LLONG_MAX/4;
            vector<pair<long long,int>> dist(m,{INF,0}); vector<int> par(m,-1);
            for(int y=0;y<m;y++) if(!inS[y]&&src[y]) dist[y]={-ew[y],0};
            bool ch=true;
            while(ch){ ch=false;
                for(int u=0;u<m;u++) if(dist[u].first<INF) for(int v=0;v<m;v++) if(g[u][v]){
                    pair<long long,int> nd={dist[u].first+(inS[v]?ew[v]:-ew[v]),dist[u].second+1};
                    if(nd<dist[v]){ dist[v]=nd; par[v]=u; ch=true; }
                }
            }
            int best=-1;
            for(int y=0;y<m;y++) if(!inS[y]&&snk[y]&&dist[y].first<INF) if(best<0||dist[y]<dist[best]) best=y;
            if(best<0) break;
            removedW-=dist[best].first;
            for(int v=best;v>=0;v=par[v]) inS[v]=!inS[v];
            sz++; ans[m-sz]=total-removedW;
        }
    }
    for(int k=1;k<=m;k++) printf("%lld\n",ans[k]);
}
