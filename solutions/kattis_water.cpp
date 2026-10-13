#include <bits/stdc++.h>
using namespace std;
int n; int cap[101][101]; int lvl[101], it[101];
bool bfs(){
    fill(lvl,lvl+n+1,-1); lvl[1]=0; queue<int> q; q.push(1);
    while(!q.empty()){int u=q.front();q.pop();for(int v=1;v<=n;v++) if(cap[u][v]>0&&lvl[v]<0){lvl[v]=lvl[u]+1;q.push(v);}}
    return lvl[2]>=0;
}
int dfs(int u,int f){
    if(u==2) return f;
    for(int &v=it[u];v<=n;v++){
        if(cap[u][v]>0&&lvl[v]==lvl[u]+1){
            int d=dfs(v,min(f,cap[u][v]));
            if(d>0){cap[u][v]-=d;cap[v][u]+=d;return d;}
        }
    }
    return 0;
}
long long aug(){
    long long r=0;
    while(bfs()){
        fill(it,it+n+1,1);
        int d; while((d=dfs(1,INT_MAX))>0) r+=d;
    }
    return r;
}
int main(){
    int p,k; scanf("%d %d %d",&n,&p,&k);
    for(int i=0;i<p;i++){int a,b,c;scanf("%d %d %d",&a,&b,&c);cap[a][b]+=c;cap[b][a]+=c;}
    long long f=aug(); printf("%lld\n",f);
    while(k--){int a,b,c;scanf("%d %d %d",&a,&b,&c);cap[a][b]+=c;cap[b][a]+=c;f+=aug();printf("%lld\n",f);}
}
