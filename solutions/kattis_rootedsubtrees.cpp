#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,q; scanf("%d %d",&n,&q);
    vector<vector<int>> g(n+1);
    for(int i=0;i<n-1;i++){int u,v;scanf("%d %d",&u,&v);g[u].push_back(v);g[v].push_back(u);}
    const int LG=18;
    vector<array<int,LG>> up(n+1);
    vector<int> dep(n+1,0),order; order.reserve(n);
    vector<char> vis(n+1,0);
    order.push_back(1); vis[1]=1; up[1].fill(1);
    for(size_t h=0;h<order.size();h++){
        int v=order[h];
        for(int w:g[v]) if(!vis[w]){
            vis[w]=1; dep[w]=dep[v]+1; up[w][0]=v;
            for(int j=1;j<LG;j++) up[w][j]=up[up[w][j-1]][j-1];
            order.push_back(w);
        }
    }
    while(q--){
        int a,b; scanf("%d %d",&a,&b);
        int x=a,y=b;
        if(dep[x]<dep[y]) swap(x,y);
        int df=dep[x]-dep[y];
        for(int j=0;j<LG;j++) if(df>>j&1) x=up[x][j];
        if(x!=y){
            for(int j=LG-1;j>=0;j--) if(up[x][j]!=up[y][j]){x=up[x][j];y=up[y][j];}
            x=up[x][0];
        }
        long long d=dep[a]+dep[b]-2*dep[x]+1;
        printf("%lld\n",(long long)n+d*(d-1)/2);
    }
}
