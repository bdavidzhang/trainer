#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<vector<pair<int,int>>> g(n+1);
    for(int i=0;i<n-1;i++){ int a,b,w; scanf("%d %d %d",&a,&b,&w); g[a].push_back({b,w}); g[b].push_back({a,w}); }
    int m; scanf("%d",&m);
    vector<int> par(n+1,0);
    for(int i=0;i<m;i++){ int a,b; scanf("%d %d",&a,&b); par[a]^=1; par[b]^=1; }
    // the set of streets is forced: the unique T-join of the tree for odd-degree vertices
    vector<int> order, pa(n+1,0), pw(n+1,0);
    order.reserve(n); order.push_back(1); pa[1]=-1;
    for(size_t i=0;i<order.size();i++){ int u=order[i]; for(auto [v,w]:g[u]) if(v!=pa[u]){ pa[v]=u; pw[v]=w; order.push_back(v);} }
    long long ans=0;
    for(int i=n-1;i>0;i--){ int u=order[i]; if(par[u]){ ans+=pw[u]; par[pa[u]]^=1; } }
    printf("%lld\n",ans);
}
