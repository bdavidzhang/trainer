#include <bits/stdc++.h>
using namespace std;
// Fractional perfect matching <=> perfect matching in bipartite double cover. x_ij = 5000*(M(i->j)+M(j->i)).
int n,m;vector<vector<int>> adj;vector<int> ml,mr,dist_;
bool bfs(){queue<int>q;bool f=false;for(int i=0;i<n;i++){if(ml[i]<0){dist_[i]=0;q.push(i);}else dist_[i]=-1;}
    while(!q.empty()){int u=q.front();q.pop();for(int v:adj[u]){int w=mr[v];if(w<0)f=true;else if(dist_[w]<0){dist_[w]=dist_[u]+1;q.push(w);}}}
    return f;}
bool dfs(int u){for(int v:adj[u]){int w=mr[v];if(w<0||(dist_[w]==dist_[u]+1&&dfs(w))){ml[u]=v;mr[v]=u;return true;}}dist_[u]=-1;return false;}
int main(){scanf("%d %d",&n,&m);adj.resize(n);for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);a--;b--;adj[a].push_back(b);adj[b].push_back(a);}
    ml.assign(n,-1);mr.assign(n,-1);dist_.assign(n,0);int cnt=0;
    while(bfs())for(int i=0;i<n;i++)if(ml[i]<0&&dfs(i))cnt++;
    if(cnt<n){puts("-1");return 0;}
    vector<vector<int>> x(n,vector<int>(n,0));
    for(int i=0;i<n;i++){x[i][ml[i]]+=5000;x[ml[i]][i]+=5000;}
    string out;for(int i=0;i<n;i++){for(int j=0;j<n;j++){out+=to_string(x[i][j]);out+=(j+1<n?' ':'\n');}}
    fputs(out.c_str(),stdout);}
