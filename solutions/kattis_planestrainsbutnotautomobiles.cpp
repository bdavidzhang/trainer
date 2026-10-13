#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<vector<int>> g, rg;
vector<int> ml, mr, dist_, it_;
bool bfs(){
    queue<int> q; bool found=false;
    for(int u=0;u<n;u++){ if(ml[u]<0){dist_[u]=0;q.push(u);} else dist_[u]=-1; }
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:g[u]){
            int w=mr[v];
            if(w<0) found=true;
            else if(dist_[w]<0){ dist_[w]=dist_[u]+1; q.push(w); }
        }
    }
    return found;
}
bool dfs(int u){
    for(int&i=it_[u];i<(int)g[u].size();i++){
        int v=g[u][i], w=mr[v];
        if(w<0 || (dist_[w]==dist_[u]+1 && dfs(w))){ ml[u]=v; mr[v]=u; return true; }
    }
    dist_[u]=-1;
    return false;
}
int main(){
    scanf("%d %d",&n,&m);
    g.assign(n,{}); rg.assign(n,{});
    for(int i=0;i<m;i++){ int a,b; scanf("%d %d",&a,&b); a--;b--; g[a].push_back(b); rg[b].push_back(a); }
    ml.assign(n,-1); mr.assign(n,-1); dist_.assign(n,0); it_.assign(n,0);
    int match=0;
    while(bfs()){
        fill(it_.begin(),it_.end(),0);
        for(int u=0;u<n;u++) if(ml[u]<0 && dfs(u)) match++;
    }
    int flights=n-match-1;
    printf("%d\n",flights);
    if(flights==0){ puts(""); return 0; }
    // left vertices that can be unmatched in some max matching (can be path end)
    vector<char> canL(n,0), canR(n,0);
    {
        queue<int> q;
        for(int u=0;u<n;u++) if(ml[u]<0){canL[u]=1;q.push(u);}
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:g[u]){ int w=mr[v]; if(w>=0 && !canL[w]){canL[w]=1;q.push(w);} }
        }
    }
    {
        queue<int> q;
        for(int v=0;v<n;v++) if(mr[v]<0){canR[v]=1;q.push(v);}
        while(!q.empty()){
            int v=q.front();q.pop();
            for(int u:rg[v]){ int w=ml[u]; if(w>=0 && !canR[w]){canR[w]=1;q.push(w);} }
        }
    }
    bool first=true;
    for(int i=0;i<n;i++) if(canL[i]||canR[i]){ printf(first?"%d":" %d",i+1); first=false; }
    puts("");
}
