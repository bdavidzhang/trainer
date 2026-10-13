#include <bits/stdc++.h>
using namespace std;
struct Dinic{
    struct E{int to,cap;};
    vector<E> e; vector<vector<int>> g; vector<int> lv,it;
    Dinic(int n):g(n),lv(n),it(n){}
    void add(int u,int v,int c){ g[u].push_back(e.size()); e.push_back({v,c}); g[v].push_back(e.size()); e.push_back({u,0}); }
    bool bfs(int s,int t){
        fill(lv.begin(),lv.end(),-1); lv[s]=0; queue<int>q; q.push(s);
        while(!q.empty()){int u=q.front();q.pop(); for(int id:g[u]) if(e[id].cap>0&&lv[e[id].to]<0){lv[e[id].to]=lv[u]+1;q.push(e[id].to);} }
        return lv[t]>=0;
    }
    int dfs(int u,int t,int f){
        if(u==t) return f;
        for(int&i=it[u];i<(int)g[u].size();i++){ int id=g[u][i]; int v=e[id].to;
            if(e[id].cap>0&&lv[v]==lv[u]+1){ int d=dfs(v,t,min(f,e[id].cap)); if(d>0){e[id].cap-=d;e[id^1].cap+=d;return d;} } }
        return 0;
    }
    int flow(int s,int t){ int r=0; while(bfs(s,t)){ fill(it.begin(),it.end(),0); int f; while((f=dfs(s,t,INT_MAX))>0) r+=f; } return r; }
};
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<pair<int,int>> ed(m); for(auto&p:ed){scanf("%d %d",&p.first,&p.second);p.first--;p.second--;}
    static char buf[5000]; scanf("%s",buf);
    const int INF=1e9;
    int s=2*n,t=2*n+1; Dinic D(2*n+2);
    // label x in {0,1,2}; node v1 = [x>=1], v2=[x>=2]. side0: 0=no-jersey,1=removed,2=jersey; side1 reversed.
    for(int v=0;v<n;v++){
        int c0,c2; if(buf[v]=='0'){c0=0;c2=1;} else {c0=1;c2=0;}
        D.add(s,2*v,c0); D.add(2*v,2*v+1,2); D.add(2*v+1,t,c2); D.add(2*v+1,2*v,INF);
    }
    for(auto&p:ed){ int u=p.first,v=p.second; D.add(2*u+1,2*v,INF); D.add(2*v+1,2*u,INF); }
    printf("%d\n",D.flow(s,t));
}
