#include <bits/stdc++.h>
using namespace std;
const int N=50005, LG=17;
int n,q,up[LG][N],dep[N];
vector<int> adj[N];
int lca(int a,int b){
    if(dep[a]<dep[b]) swap(a,b);
    int d=dep[a]-dep[b];
    for(int j=0;j<LG;j++) if(d>>j&1) a=up[j][a];
    if(a==b) return a;
    for(int j=LG-1;j>=0;j--) if(up[j][a]!=up[j][b]){a=up[j][a];b=up[j][b];}
    return up[0][a];
}
int dist(int a,int b){ return dep[a]+dep[b]-2*dep[lca(a,b)]; }
bool on(int x,int c,int d){ return dist(c,x)+dist(x,d)==dist(c,d); }
bool inter(int a,int b,int c,int d){
    return on(lca(a,b),c,d) || on(lca(c,d),a,b);
}
int main(){
    scanf("%d %d",&n,&q);
    vector<pair<int,int>> es(n+1);
    for(auto&e:es){ scanf("%d %d",&e.first,&e.second); adj[e.first].push_back(e.second); adj[e.second].push_back(e.first); }
    // BFS tree
    vector<int> par(n+1,0); vector<char> vis(n+1,0);
    queue<int> Q; Q.push(1); vis[1]=1; par[1]=1; dep[1]=0;
    while(!Q.empty()){ int x=Q.front(); Q.pop(); for(int y:adj[x]) if(!vis[y]){vis[y]=1;par[y]=x;dep[y]=dep[x]+1;Q.push(y);} }
    vector<pair<int,int>> ex;
    for(auto&e:es) if(par[e.first]!=e.second && par[e.second]!=e.first) ex.push_back(e);
    for(int i=1;i<=n;i++) up[0][i]=par[i];
    for(int j=1;j<LG;j++) for(int i=1;i<=n;i++) up[j][i]=up[j-1][up[j-1][i]];
    int A[2]={ex[0].first,ex[1].first}, B[2]={ex[0].second,ex[1].second};
    while(q--){
        int u,v; scanf("%d %d",&u,&v);
        int ans=1;
        for(int e=0;e<2;e++) for(int d=0;d<2;d++){
            int x=d?B[e]:A[e], y=d?A[e]:B[e];
            if(!inter(u,x,y,v)) ans++;
        }
        for(int e=0;e<2;e++) for(int d1=0;d1<2;d1++) for(int d2=0;d2<2;d2++){
            int f=1-e;
            int x1=d1?B[e]:A[e], y1=d1?A[e]:B[e];
            int x2=d2?B[f]:A[f], y2=d2?A[f]:B[f];
            if(inter(u,x1,y1,x2)) continue;
            if(inter(u,x1,y2,v)) continue;
            if(inter(y1,x2,y2,v)) continue;
            ans++;
        }
        printf("%d\n",ans);
    }
}
