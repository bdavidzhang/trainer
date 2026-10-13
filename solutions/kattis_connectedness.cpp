#include <bits/stdc++.h>
using namespace std;
int p[1000005];
int f(int x){while(p[x]!=x){p[x]=p[p[x]];x=p[x];}return x;}
int main(){int n,m;scanf("%d %d",&n,&m);for(int i=1;i<=n;i++)p[i]=i;int comp=n;
if(comp==1){puts("0");return 0;}
for(int i=1;i<=m;i++){int u,v;scanf("%d %d",&u,&v);u=f(u);v=f(v);if(u!=v){p[u]=v;comp--;if(comp==1){printf("%d\n",i);return 0;}}}
puts("-1");}
