#include <bits/stdc++.h>
using namespace std;
int par[400005]; int fnd(int x){ while(par[x]!=x){par[x]=par[par[x]];x=par[x];} return x; }
int up[20][400005], val[400005], sz[400005], dep[400005], top_[400005];
int main(){
    int n,m,q; scanf("%d %d %d",&n,&m,&q);
    vector<array<int,3>> e(m); for(auto&x:e) scanf("%d %d %d",&x[1],&x[2],&x[0]);
    sort(e.begin(),e.end());
    int cnt=n;
    for(int i=1;i<=2*n;i++){par[i]=i; sz[i]=i<=n?1:0; val[i]=-1;}
    vector<int> tp(2*n+1,0);
    for(auto&x:e){ int a=fnd(x[1]),b=fnd(x[2]); if(a==b) continue;
        ++cnt; val[cnt]=x[0]; sz[cnt]=sz[a]+sz[b]; par[a]=par[b]=cnt; tp[a]=tp[b]=cnt; }
    int root=cnt; tp[root]=root;
    for(int v=root;v>=1;v--){
        up[0][v]=tp[v];
        if(v==root){dep[v]=0; top_[v]=v;}
        else { dep[v]=dep[tp[v]]+1; top_[v]=(val[tp[v]]==val[v])?top_[tp[v]]:v; }
    }
    for(int k=1;k<20;k++) for(int v=1;v<=root;v++) up[k][v]=up[k-1][up[k-1][v]];
    while(q--){ int a,b; scanf("%d %d",&a,&b);
        if(dep[a]<dep[b]) swap(a,b);
        int d=dep[a]-dep[b]; for(int k=0;k<20;k++) if(d>>k&1) a=up[k][a];
        if(a!=b){ for(int k=19;k>=0;k--) if(up[k][a]!=up[k][b]){a=up[k][a];b=up[k][b];} a=up[0][a]; }
        int t=top_[a];
        printf("%d %d\n",val[t],sz[t]);
    }
}
