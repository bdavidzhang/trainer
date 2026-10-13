#include <bits/stdc++.h>
using namespace std;
int N;vector<vector<int>> g,gr;vector<int> ord,comp;vector<char> vis;
void d1(int u){vis[u]=1;for(int v:g[u])if(!vis[v])d1(v);ord.push_back(u);}
void d2(int u,int c){comp[u]=c;for(int v:gr[u])if(comp[v]<0)d2(v,c);}
void imp(int a,int b){g[a].push_back(b);gr[b].push_back(a);}
int main(){int n,r,k;cin>>n>>r>>k;vector<int>x(k),y(k);for(int i=0;i<k;i++)cin>>x[i]>>y[i];
 N=2*k;g.resize(N);gr.resize(N);
 // var i true (node 2i) = lights its row; false (2i+1) = column
 for(int i=0;i<k;i++)for(int j=i+1;j<k;j++){
  if(x[i]==x[j]&&abs(y[i]-y[j])<=2*r){imp(2*i,2*j+1);imp(2*j,2*i+1);}
  if(y[i]==y[j]&&abs(x[i]-x[j])<=2*r){imp(2*i+1,2*j);imp(2*j+1,2*i);}
 }
 vis.assign(N,0);comp.assign(N,-1);
 for(int i=0;i<N;i++)if(!vis[i])d1(i);
 int c=0;for(int i=N-1;i>=0;i--)if(comp[ord[i]]<0)d2(ord[i],c++);
 for(int i=0;i<k;i++)if(comp[2*i]==comp[2*i+1]){puts("0");return 0;}
 puts("1");}
