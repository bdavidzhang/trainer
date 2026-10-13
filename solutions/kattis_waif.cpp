#include <bits/stdc++.h>
using namespace std;
struct E{int to,cap;};
vector<E> es; vector<vector<int>> adj; vector<int> lvl,it;
void add(int u,int v,int c){adj[u].push_back(es.size());es.push_back({v,c});adj[v].push_back(es.size());es.push_back({u,0});}
bool bfs(int s,int t){
    fill(lvl.begin(),lvl.end(),-1);lvl[s]=0;queue<int>q;q.push(s);
    while(!q.empty()){int u=q.front();q.pop();for(int id:adj[u])if(es[id].cap>0&&lvl[es[id].to]<0){lvl[es[id].to]=lvl[u]+1;q.push(es[id].to);}}
    return lvl[t]>=0;
}
int dfs(int u,int t,int f){
    if(u==t)return f;
    for(int&i=it[u];i<(int)adj[u].size();i++){
        int id=adj[u][i];
        if(es[id].cap>0&&lvl[es[id].to]==lvl[u]+1){
            int d=dfs(es[id].to,t,min(f,es[id].cap));
            if(d>0){es[id].cap-=d;es[id^1].cap+=d;return d;}
        }
    }
    return 0;
}
int main(){
    int n,m,p; scanf("%d %d %d",&n,&m,&p);
    int S=0,T=n+m+p+1,V=T+1;
    adj.assign(V,{});lvl.assign(V,0);it.assign(V,0);
    for(int i=1;i<=n;i++){
        add(S,i,1);
        int k;scanf("%d",&k);
        while(k--){int t;scanf("%d",&t);add(i,n+t,1);}
    }
    vector<char> incat(m+1,0);
    for(int j=1;j<=p;j++){
        int l;scanf("%d",&l);
        while(l--){int t;scanf("%d",&t);incat[t]=1;add(n+t,n+m+j,1);}
        int r;scanf("%d",&r);add(n+m+j,T,r);
    }
    for(int t=1;t<=m;t++)if(!incat[t])add(n+t,T,1);
    int flow=0;
    while(bfs(S,T)){fill(it.begin(),it.end(),0);int f;while((f=dfs(S,T,INT_MAX))>0)flow+=f;}
    printf("%d\n",flow);
}
