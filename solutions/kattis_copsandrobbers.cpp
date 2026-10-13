#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct E{int to;ll c;};
vector<E>es;vector<vector<int>>g;vector<int>lv,it;
void add(int a,int b,ll c){g[a].push_back(es.size());es.push_back({b,c});g[b].push_back(es.size());es.push_back({a,0});}
bool bfs(int s,int t){fill(lv.begin(),lv.end(),-1);lv[s]=0;queue<int>q;q.push(s);while(!q.empty()){int u=q.front();q.pop();for(int id:g[u])if(es[id].c>0&&lv[es[id].to]<0){lv[es[id].to]=lv[u]+1;q.push(es[id].to);}}return lv[t]>=0;}
ll dfs(int u,int t,ll f){if(u==t)return f;for(int&i=it[u];i<(int)g[u].size();i++){int id=g[u][i];int v=es[id].to;if(es[id].c>0&&lv[v]==lv[u]+1){ll d=dfs(v,t,min(f,es[id].c));if(d>0){es[id].c-=d;es[id^1].c+=d;return d;}}}return 0;}
int main(){int W,H,c;cin>>W>>H>>c;vector<string>gr(H);for(auto&s:gr)cin>>s;vector<ll>cost(c);for(auto&x:cost)cin>>x;
 const ll INF=1e15;int V=2*W*H+1,T=2*W*H,S=-1;g.assign(V,{});lv.assign(V,0);it.assign(V,0);
 int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
 for(int i=0;i<H;i++)for(int j=0;j<W;j++){int id=i*W+j;char ch=gr[i][j];if(ch=='B')S=2*id+1;
  add(2*id,2*id+1,(ch=='B'||ch=='.')?INF:cost[ch-'a']);
  for(int k=0;k<4;k++){int a=i+dx[k],b=j+dy[k];if(a<0||b<0||a>=H||b>=W)add(2*id+1,T,INF);else add(2*id+1,2*(a*W+b),INF);}}
 ll fl=0;while(bfs(S,T)){fill(it.begin(),it.end(),0);ll f;while((f=dfs(S,T,INF))>0){fl+=f;if(fl>=INF)break;}if(fl>=INF)break;}
 cout<<(fl>=INF?-1:fl)<<endl;}
