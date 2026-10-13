#include <bits/stdc++.h>
using namespace std;
struct Dinic{struct E{int to;long long c;};vector<E>es;vector<vector<int>>g;vector<int>lv,it;
 Dinic(int n):g(n),lv(n),it(n){}
 void add(int a,int b,long long c){g[a].push_back(es.size());es.push_back({b,c});g[b].push_back(es.size());es.push_back({a,0});}
 bool bfs(int s,int t){fill(lv.begin(),lv.end(),-1);lv[s]=0;queue<int>q;q.push(s);while(!q.empty()){int u=q.front();q.pop();for(int id:g[u])if(es[id].c>0&&lv[es[id].to]<0){lv[es[id].to]=lv[u]+1;q.push(es[id].to);}}return lv[t]>=0;}
 long long dfs(int u,int t,long long f){if(u==t)return f;for(int&i=it[u];i<(int)g[u].size();i++){int id=g[u][i];int v=es[id].to;if(es[id].c>0&&lv[v]==lv[u]+1){long long d=dfs(v,t,min(f,es[id].c));if(d>0){es[id].c-=d;es[id^1].c+=d;return d;}}}return 0;}
 long long flow(int s,int t){long long r=0;while(bfs(s,t)){fill(it.begin(),it.end(),0);while(long long f=dfs(s,t,LLONG_MAX))r+=f;}return r;}
};
int main(){int n,m;scanf("%d %d",&n,&m);vector<int>a(m),b(m),d(m);long long tot=0;
for(int i=0;i<m;i++){scanf("%d %d %d",&a[i],&b[i],&d[i]);a[i]--;b[i]--;tot+=d[i];}
auto ok=[&](long long B){Dinic D(n+m+2);int S=n+m,T=S+1;for(int i=0;i<m;i++){D.add(S,n+i,d[i]);D.add(n+i,a[i],d[i]);D.add(n+i,b[i],d[i]);}
 for(int i=0;i<n;i++)D.add(i,T,B);return D.flow(S,T)==B*n;};
long long lo=0,hi=tot/n;while(lo<hi){long long mid=(lo+hi+1)/2;if(ok(mid))lo=mid;else hi=mid-1;}
printf("%lld\n",tot-lo*n);}
