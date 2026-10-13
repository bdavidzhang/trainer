#include <bits/stdc++.h>
using namespace std;
struct E{int to,cap;};
vector<E>es;vector<vector<int>>g;vector<int>lvl,it;
void add(int a,int b,int c){g[a].push_back(es.size());es.push_back({b,c});g[b].push_back(es.size());es.push_back({a,0});}
bool bfs(int s,int t){fill(lvl.begin(),lvl.end(),-1);lvl[s]=0;queue<int>q;q.push(s);while(!q.empty()){int u=q.front();q.pop();for(int id:g[u])if(es[id].cap>0&&lvl[es[id].to]<0){lvl[es[id].to]=lvl[u]+1;q.push(es[id].to);}}return lvl[t]>=0;}
int dfs(int u,int t,int f){if(u==t)return f;for(int&i=it[u];i<(int)g[u].size();i++){int id=g[u][i];int v=es[id].to;if(es[id].cap>0&&lvl[v]==lvl[u]+1){int d=dfs(v,t,min(f,es[id].cap));if(d>0){es[id].cap-=d;es[id^1].cap+=d;return d;}}}return 0;}
int main(){int w,h;cin>>w>>h;vector<string>a(h);for(auto&r:a)cin>>r;
 const int INF=1e9;int n=w*h,S=2*n,T=2*n+1;g.resize(2*n+2);lvl.resize(2*n+2);it.resize(2*n+2);
 int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
 for(int i=0;i<h;i++)for(int j=0;j<w;j++){int u=i*w+j;char c=a[i][j];
  if(c=='A'){add(S,u,INF);add(u,u+n,INF);}else if(c=='B'){add(u,u+n,INF);add(u+n,T,INF);}else add(u,u+n,c-'0');
  for(int d=0;d<4;d++){int x=i+dx[d],y=j+dy[d];if(x<0||y<0||x>=h||y>=w)continue;add(u+n,x*w+y,INF);}}
 long long fl=0;while(bfs(S,T)){fill(it.begin(),it.end(),0);int f;while((f=dfs(S,T,INF))>0)fl+=f;}
 cout<<fl<<endl;}
