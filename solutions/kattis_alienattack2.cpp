#include <bits/stdc++.h>
using namespace std;
int p[200005],sz[200005];
int fd(int x){while(p[x]!=x)x=p[x]=p[p[x]];return x;}
int main(){int n,m;scanf("%d %d",&n,&m);for(int i=1;i<=n;i++)p[i]=i,sz[i]=1;int best=1;
 while(m--){int a,b;scanf("%d %d",&a,&b);a=fd(a);b=fd(b);if(a!=b){if(sz[a]<sz[b])swap(a,b);p[b]=a;sz[a]+=sz[b];best=max(best,sz[a]);}}
 printf("%d\n",best);}
