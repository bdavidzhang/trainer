#include <bits/stdc++.h>
using namespace std;
int main(){int n,g,d;long long m;if(scanf("%d %d %d %lld",&n,&g,&d,&m)!=4)return 0;
 const int MX=1000001;vector<int>start(n);for(auto&x:start)scanf("%d",&x);
 vector<vector<int>>gen(g);for(auto&v:gen){int k;scanf("%d",&k);v.resize(k);for(auto&x:v)scanf("%d",&x);}
 vector<int>head(MX,-1),nxt(d),to(d);for(int i=0;i<d;i++){int a,b;scanf("%d %d",&a,&b);to[i]=b;nxt[i]=head[a];head[a]=i;}
 vector<char>vis(MX,0);vector<int>st;long long cnt=0;for(int x:start)if(!vis[x]){vis[x]=1;st.push_back(x);cnt++;}
 while(!st.empty()){int u=st.back();st.pop_back();for(int e=head[u];e!=-1;e=nxt[e])if(!vis[to[e]]){vis[to[e]]=1;cnt++;st.push_back(to[e]);}}
 bool ok=false;if(cnt<=m)for(auto&v:gen){long long c=0;for(int x:v)if(vis[x])c++;if(c==cnt){ok=true;break;}}
 puts(ok?"masterpiece":"disaster");}
