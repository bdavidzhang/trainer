#include <bits/stdc++.h>
using namespace std;
// Planar graph with min degree 3 has girth <= 5, so answer is 3, 4 or 5.
int main(){
    int n,m; scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){int x,y;scanf("%d %d",&x,&y);}
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);a--;b--;adj[a].push_back(b);adj[b].push_back(a);}
    // rank by (degree, id)
    vector<int> ord(n),rk(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int a,int b){return adj[a].size()!=adj[b].size()?adj[a].size()<adj[b].size():a<b;});
    for(int i=0;i<n;i++) rk[ord[i]]=i;
    // triangles
    vector<vector<int>> out(n);
    for(int u=0;u<n;u++) for(int v:adj[u]) if(rk[u]<rk[v]) out[u].push_back(v);
    vector<int> mark(n,-1);
    for(int u=0;u<n;u++){
        for(int v:out[u]) mark[v]=u;
        for(int v:out[u]) for(int w:out[v]) if(mark[w]==u){puts("3");return 0;}
    }
    // 4-cycles: a = highest rank vertex, count paths a-b-c with rk[b]<rk[a], rk[c]<rk[a]
    vector<int> cnt(n,0);
    for(int a=0;a<n;a++){
        bool found=false;
        for(int b:adj[a]) if(rk[b]<rk[a]){
            for(int c:adj[b]){ if(rk[c]>=rk[a]) continue; if(++cnt[c]>=2) found=true; }
        }
        if(found){puts("4");return 0;}
        for(int b:adj[a]) if(rk[b]<rk[a]) for(int c:adj[b]) if(rk[c]<rk[a]) cnt[c]=0;
    }
    puts("5");
}
