#include <bits/stdc++.h>
using namespace std;

int main(){int n,m;scanf("%d %d",&n,&m);vector<vector<int>>g(n+1);for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);}
vector<int>d(n+1,-1);d[1]=0;queue<int>q;q.push(1);while(!q.empty()){int u=q.front();q.pop();for(int v:g[u])if(d[v]<0){d[v]=d[u]+1;q.push(v);}}
printf("%d\n",d[n]-1);}
