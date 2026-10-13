#include <bits/stdc++.h>
using namespace std;
int n,q;vector<vector<int>>g;
static void bfs(int s,vector<int>&d,vector<int>&ord){ord.clear();d[s]=0;ord.push_back(s);for(size_t h=0;h<ord.size();h++){int u=ord[h];for(int w:g[u])if(d[w]<0){d[w]=d[u]+1;ord.push_back(w);}}}
int main(){scanf("%d %d",&n,&q);g.resize(n+1);for(int i=0;i<n-3;i++){int x,y;scanf("%d %d",&x,&y);g[x].push_back(y);g[y].push_back(x);}
 vector<int>comp(n+1,-1),ecc(n+1,0),d0(n+1,-1),d1(n+1,-1),d2(n+1,-1),ord;int diam[3]={0,0,0};int c=0;
 for(int s=1;s<=n;s++)if(comp[s]<0){bfs(s,d0,ord);int u=ord.back();vector<int>nodes=ord;bfs(u,d1,ord);int w=ord.back();bfs(w,d2,ord);
  for(int x:nodes){comp[x]=c;ecc[x]=max(d1[x],d2[x])+1;}diam[c]=d1[w]+1;c++;}
 while(q--){int a,b;scanf("%d %d",&a,&b);printf("%d\n",ecc[a]+ecc[b]+diam[3-comp[a]-comp[b]]);}}
