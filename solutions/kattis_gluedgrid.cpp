#include <bits/stdc++.h>
using namespace std;
// Tiles never leave their biconnected block (a cut vertex belongs to the block towards the blank).
// Inside a block (2-connected bipartite, non-cycle, or a 2x2 / single edge) exactly the even permutations are reachable.
int h,w;
int main(){
    scanf("%d %d",&h,&w);
    vector<string> g(h);
    for(auto&s:g){static char buf[600];scanf("%s",buf);s=buf;}
    int N=h*w; vector<int> a(N);
    for(int i=0;i<N;i++) scanf("%d",&a[i]);
    vector<int> disc(N,-1),low(N,0),par(N,-1),order,it(N,0),grp(N,-1);
    int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
    int root=N-1,timer=0;
    vector<int> st; st.push_back(root); disc[root]=low[root]=timer++; order.push_back(root);
    while(!st.empty()){
        int u=st.back();
        if(it[u]<4){
            int d=it[u]++; int r=u/w+dx[d],c=u%w+dy[d];
            if(r<0||c<0||r>=h||c>=w||g[r][c]=='#') continue;
            int v=r*w+c;
            if(v==par[u]) continue;
            if(disc[v]<0){par[v]=u;disc[v]=low[v]=timer++;order.push_back(v);st.push_back(v);}
            else low[u]=min(low[u],disc[v]);
        } else {
            st.pop_back();
            if(par[u]>=0) low[par[u]]=min(low[par[u]],low[u]);
        }
    }
    int ng=0;
    for(int v:order){ if(v==root) continue; int p=par[v];
        if(p==root||low[v]>=disc[p]) grp[v]=ng++; else grp[v]=grp[p]; }
    bool ok=true;
    vector<int> parity(ng,0); vector<char> seen(N,0);
    for(int v=0;v<N&&ok;v++){
        if(v==root||g[v/w][v%w]=='#') continue;
        if(disc[v]<0){ if(a[v]-1!=v) ok=false; continue; }
        int t=a[v]-1;
        if(t<0||t==root||g[t/w][t%w]=='#'||disc[t]<0||grp[t]!=grp[v]){ok=false;break;}
    }
    if(ok){
        for(int v=0;v<N;v++){
            if(v==root||g[v/w][v%w]=='#'||disc[v]<0||seen[v]) continue;
            int len=0,c=v; while(!seen[c]){seen[c]=1;len++;c=a[c]-1;}
            parity[grp[v]]^=(len-1)&1;
        }
        for(int i=0;i<ng;i++) if(parity[i]) ok=false;
    }
    puts(ok?"possible":"impossible");
}
