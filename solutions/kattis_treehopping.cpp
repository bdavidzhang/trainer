#include <bits/stdc++.h>
using namespace std;
int main(){int T;scanf("%d",&T);while(T--){int n;scanf("%d",&n);vector<vector<int>>g(n+1);for(int i=0;i<n-1;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);}
 vector<int>par(n+1,0),dep(n+1,0),q;q.push_back(1);par[1]=0;for(size_t h=0;h<q.size();h++){int u=q[h];for(int w:g[u])if(w!=par[u]){par[w]=u;dep[w]=dep[u]+1;q.push_back(w);}}
 vector<int>p(n);for(auto&x:p)scanf("%d",&x);bool ok=true;
 for(int i=0;i+1<n&&ok;i++){int a=p[i],b=p[i+1],d=0;while(a!=b&&d<=3){if(dep[a]<dep[b])swap(a,b);a=par[a];d++;}if(a!=b||d>3)ok=false;}
 puts(ok?"1":"0");}}
