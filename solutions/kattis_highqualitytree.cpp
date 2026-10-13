#include <bits/stdc++.h>
using namespace std;
const int B=32; const int INF=1e9;
int main(){
    int n; scanf("%d",&n);
    vector<vector<int>> adj(n+1);
    for(int i=0;i<n-1;i++){int u,v;scanf("%d %d",&u,&v);adj[u].push_back(v);adj[v].push_back(u);}
    vector<int> par(n+1,0),order; order.reserve(n);
    vector<int> st={1}; par[1]=0;
    while(!st.empty()){int v=st.back();st.pop_back();order.push_back(v);for(int u:adj[v]) if(u!=par[v]){par[u]=v;st.push_back(u);}}
    // f[v][h]: min removals so subtree v is strongly balanced with height exactly h (0 = empty)
    vector<array<int,B>> f(n+1);
    vector<int> sz(n+1,1);
    array<int,B> nul; nul.fill(INF); nul[0]=0;
    for(int idx=n-1;idx>=0;idx--){
        int v=order[idx];
        const array<int,B>* c[2]={&nul,&nul}; int k=0;
        for(int u:adj[v]) if(u!=par[v]){ c[k++]=&f[u]; sz[v]+=sz[u]; }
    }
    for(int idx=n-1;idx>=0;idx--){
        int v=order[idx];
        const array<int,B>* c[2]={&nul,&nul}; int k=0;
        for(int u:adj[v]) if(u!=par[v]) c[k++]=&f[u];
        const auto&L=*c[0];const auto&R=*c[1];
        f[v].fill(INF); f[v][0]=sz[v];
        for(int h=1;h<B;h++){
            int best=INF;
            if(L[h-1]<INF&&R[h-1]<INF) best=min(best,L[h-1]+R[h-1]);
            if(h>=2){
                if(L[h-1]<INF&&R[h-2]<INF) best=min(best,L[h-1]+R[h-2]);
                if(L[h-2]<INF&&R[h-1]<INF) best=min(best,L[h-2]+R[h-1]);
            }
            f[v][h]=best;
        }
    }
    int ans=INF; for(int h=0;h<B;h++) ans=min(ans,f[1][h]);
    printf("%d\n",ans);
}
