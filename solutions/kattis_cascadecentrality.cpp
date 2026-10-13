#include <bits/stdc++.h>
using namespace std;
int n;vector<int> g[105];
double dfs(int v,int p,double pr){double s=0;for(int w:g[v])if(w!=p){double q=pr/g[w].size();s+=q+dfs(w,v,q);}return s;}
int main(){scanf("%d",&n);for(int i=0;i<n-1;i++){int u,v;scanf("%d %d",&u,&v);g[u].push_back(v);g[v].push_back(u);}
 double t=0;for(int i=1;i<=n;i++)t+=1+dfs(i,0,1.0);
 printf("%.9f\n",t/n);}
