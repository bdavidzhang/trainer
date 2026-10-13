#include <bits/stdc++.h>
using namespace std;
struct E{int to,cap;};
vector<E> es; vector<vector<int>> g; vector<int> lvl,it;
void add(int u,int v,int c){es.push_back({v,c});g[u].push_back(es.size()-1);es.push_back({u,0});g[v].push_back(es.size()-1);}
vector<int> par;
bool augment(int s,int t){
    fill(par.begin(),par.end(),-1); par[s]=-2; queue<int> q; q.push(s);
    while(!q.empty()&&par[t]==-1){int u=q.front();q.pop(); for(int id:g[u]) if(es[id].cap>0&&par[es[id].to]==-1){par[es[id].to]=id;q.push(es[id].to);}}
    if(par[t]==-1) return false;
    for(int v=t;v!=s;){int id=par[v]; es[id].cap--; es[id^1].cap++; v=es[id^1].to;}
    return true;
}
int main(){
    int n,k,m; scanf("%d %d %d",&n,&k,&m);
    int S=n*k, T=n*k+1;
    g.assign(n*k+2,{}); lvl.assign(n*k+2,0); it.assign(n*k+2,0);
    auto id=[&](int v,int t){return (v-1)*k+t;};
    for(int i=0;i<m;i++){
        int a,b; scanf("%d %d",&a,&b);
        if(a==n) continue;
        for(int t=0;t<k;t++) add(id(a,t),id(b,(t+1)%k),1);
    }
    for(int j=1;j<=k;j++) add(S,id(j,j%k),1);
    for(int t=0;t<k;t++) add(id(n,t),T,1000000);
    int flow=0; par.assign(n*k+2,-1);
    while(augment(S,T)) flow++;
    printf("%d\n",flow);
}
