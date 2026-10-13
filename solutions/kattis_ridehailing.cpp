#include <bits/stdc++.h>
using namespace std;
int n,m,k; int d[105][105];
vector<vector<int>> adj; vector<int> ml,mr,dist_;
bool bfs(){
    queue<int> q; bool found=false;
    for(int i=0;i<k;i++){ if(ml[i]<0){dist_[i]=0;q.push(i);} else dist_[i]=-1; }
    while(!q.empty()){int u=q.front();q.pop();
        for(int v:adj[u]){int w=mr[v]; if(w<0) found=true; else if(dist_[w]<0){dist_[w]=dist_[u]+1;q.push(w);}}}
    return found;
}
vector<int> itp;
bool dfs(int u){
    for(int &i=itp[u];i<(int)adj[u].size();i++){int v=adj[u][i];int w=mr[v];
        if(w<0||(dist_[w]==dist_[u]+1&&dfs(w))){ml[u]=v;mr[v]=u;return true;}}
    dist_[u]=-1; return false;
}
int main(){
    scanf("%d %d %d",&n,&m,&k);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)d[i][j]=i==j?0:1e9;
    for(int i=0;i<m;i++){int u,v,w;scanf("%d %d %d",&u,&v,&w);d[u][v]=min(d[u][v],w);}
    for(int x=1;x<=n;x++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(d[i][x]+d[x][j]<d[i][j])d[i][j]=d[i][x]+d[x][j];
    vector<int> U(k),V(k),T(k);
    for(int i=0;i<k;i++)scanf("%d %d %d",&U[i],&V[i],&T[i]);
    adj.assign(k,{});
    for(int i=0;i<k;i++)for(int j=0;j<k;j++)if(i!=j){
        if((long long)T[i]+d[U[i]][V[i]]+d[V[i]][U[j]]<=T[j]) adj[i].push_back(j);
    }
    ml.assign(k,-1);mr.assign(k,-1);dist_.assign(k,0);
    int match=0;
    while(bfs()){itp.assign(k,0);for(int i=0;i<k;i++)if(ml[i]<0&&dfs(i))match++;}
    printf("%d\n",k-match);
}
