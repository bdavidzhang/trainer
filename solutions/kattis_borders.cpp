#include <bits/stdc++.h>
using namespace std;
int n,m;vector<string> g;vector<vector<int>> id;
vector<vector<int>> adj;vector<int> mt;vector<int> vis;int stamp=0;
bool tryk(int u){
    for(int v:adj[u])if(vis[v]!=stamp){
        vis[v]=stamp;
        if(mt[v]<0||tryk(mt[v])){mt[v]=u;return true;}
    }
    return false;
}
int main(){
    cin>>n>>m;g.resize(n);for(auto&s:g)cin>>s;
    id.assign(n,vector<int>(m,-1));
    int R=0;vector<char> forced,col;
    int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(id[i][j]<0){
        bool f=false;queue<pair<int,int>> q;q.push({i,j});id[i][j]=R;
        while(!q.empty()){
            auto [x,y]=q.front();q.pop();
            if(x==0||y==0||x==n-1||y==m-1)f=true;
            for(int d=0;d<4;d++){
                int a=x+dx[d],b=y+dy[d];
                if(a<0||b<0||a>=n||b>=m||id[a][b]>=0||g[a][b]!=g[i][j])continue;
                id[a][b]=R;q.push({a,b});
            }
        }
        forced.push_back(f);col.push_back(g[i][j]-'0');R++;
    }
    adj.assign(R,{});
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)for(int d=0;d<4;d+=2){
        int a=i+dx[d],b=j+dy[d];
        if(a>=n||b>=m)continue;
        int u=id[i][j],v=id[a][b];
        if(u==v||forced[u]||forced[v])continue;
        if(col[u])swap(u,v);
        adj[u].push_back(v);
    }
    int ans=0;
    for(int i=0;i<R;i++){ans+=forced[i];sort(adj[i].begin(),adj[i].end());adj[i].erase(unique(adj[i].begin(),adj[i].end()),adj[i].end());}
    mt.assign(R,-1);vis.assign(R,0);
    for(int i=0;i<R;i++)if(!forced[i]&&!col[i]&&!adj[i].empty()){
        stamp++;if(tryk(i))ans++;
    }
    cout<<ans<<"\n";
}
