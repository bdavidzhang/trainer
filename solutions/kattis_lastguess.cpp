#include <bits/stdc++.h>
using namespace std;
struct E{int to,cap;};
vector<E>es;vector<vector<int>>g;vector<int>lvl,it;
void add(int u,int v,int c){es.push_back({v,c});g[u].push_back(es.size()-1);es.push_back({u,0});g[v].push_back(es.size()-1);}
bool bfs(int s,int t){fill(lvl.begin(),lvl.end(),-1);lvl[s]=0;queue<int>q;q.push(s);while(!q.empty()){int u=q.front();q.pop();for(int id:g[u])if(es[id].cap>0&&lvl[es[id].to]<0){lvl[es[id].to]=lvl[u]+1;q.push(es[id].to);}}return lvl[t]>=0;}
int dfs(int u,int t,int f){if(u==t)return f;for(int&i=it[u];i<(int)g[u].size();i++){int id=g[u][i];int v=es[id].to;if(es[id].cap>0&&lvl[v]==lvl[u]+1){int d=dfs(v,t,min(f,es[id].cap));if(d>0){es[id].cap-=d;es[id^1].cap+=d;return d;}}}return 0;}
int flow(int s,int t){int r=0;while(bfs(s,t)){fill(it.begin(),it.end(),0);int f;while((f=dfs(s,t,1e9))>0)r+=f;}return r;}
int main(){int G,L;cin>>G>>L;vector<int>lo(26,0),ex(26,-1);string res(L,'?');vector<array<bool,26>>ban(L);for(auto&b:ban)b.fill(false);
 for(int q=0;q<G-1;q++){string s,t;cin>>s>>t;int cnt[26]={0};bool bl[26]={0};
  for(int i=0;i<L;i++){int c=s[i]-'a';if(t[i]=='G'){res[i]=s[i];cnt[c]++;}else{ban[i][c]=true;if(t[i]=='Y')cnt[c]++;else bl[c]=true;}}
  for(int c=0;c<26;c++){lo[c]=max(lo[c],cnt[c]);if(bl[c])ex[c]=cnt[c];}}
 int fixedc[26]={0};for(int i=0;i<L;i++)if(res[i]!='?')fixedc[res[i]-'a']++;
 int S=26+L,T=S+1;g.assign(T+1,{});lvl.assign(T+1,0);it.assign(T+1,0);
 vector<int>sid(26);
 for(int c=0;c<26;c++){sid[c]=es.size();add(S,c,max(0,lo[c]-fixedc[c]));}
 for(int i=0;i<L;i++)if(res[i]=='?'){add(26+i,T,1);for(int c=0;c<26;c++)if(!ban[i][c])add(c,26+i,1);}
 flow(S,T);
 for(int c=0;c<26;c++)if(ex[c]<0)es[sid[c]].cap+=L;
 flow(S,T);
 for(int c=0;c<26;c++)for(int id:g[c]){if(id%2==0&&es[id].to>=26&&es[id].to<26+L&&es[id].cap==0)res[es[id].to-26]='a'+c;}
 cout<<res<<"\n";}
