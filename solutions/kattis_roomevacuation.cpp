#include <bits/stdc++.h>
using namespace std;
struct E{int to,cap;};
vector<E> es; vector<vector<int>> g; vector<int> lvl,it;
void add(int u,int v,int c){ g[u].push_back(es.size()); es.push_back({v,c}); g[v].push_back(es.size()); es.push_back({u,0}); }
bool bfs(int s,int t){ fill(lvl.begin(),lvl.end(),-1); lvl[s]=0; queue<int> q; q.push(s);
    while(!q.empty()){int u=q.front();q.pop(); for(int id:g[u]) if(es[id].cap>0&&lvl[es[id].to]<0){lvl[es[id].to]=lvl[u]+1;q.push(es[id].to);} }
    return lvl[t]>=0; }
int dfs(int u,int t,int f){ if(u==t) return f;
    for(int &i=it[u];i<(int)g[u].size();i++){ int id=g[u][i]; int v=es[id].to;
        if(es[id].cap>0&&lvl[v]==lvl[u]+1){ int d=dfs(v,t,min(f,es[id].cap)); if(d>0){es[id].cap-=d;es[id^1].cap+=d;return d;} } }
    return 0; }
int main(){
    int n,m,T; scanf("%d %d %d",&n,&m,&T);
    vector<string> a(n); char buf[64];
    for(auto&r:a){scanf("%s",buf);r=buf;}
    int C=n*m; int N=C*(T+1)*2+2, S=N-2, K=N-1;
    g.assign(N,{}); lvl.assign(N,0); it.assign(N,0);
    auto in=[&](int c,int t){return (t*C+c)*2;};
    int dx[]={0,0,1,-1,0},dy[]={1,-1,0,0,0};
    for(int t=0;t<=T;t++)for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        if(a[i][j]=='#') continue; int c=i*m+j;
        add(in(c,t),in(c,t)+1,1);
        if(t==0&&a[i][j]=='P') add(S,in(c,0),1);
        if(a[i][j]=='E'){ add(in(c,t)+1,K,1); continue; }
        if(t<T) for(int d=0;d<5;d++){ int x=i+dx[d],y=j+dy[d];
            if(x<0||y<0||x>=n||y>=m||a[x][y]=='#') continue;
            add(in(c,t)+1,in(x*m+y,t+1),1); }
    }
    int flow=0;
    while(bfs(S,K)){ fill(it.begin(),it.end(),0); int f; while((f=dfs(S,K,1e9))>0) flow+=f; }
    printf("%d\n",flow);
}
