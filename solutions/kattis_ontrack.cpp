#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);int N=n+1;vector<vector<int>> g(N);
 for(int i=0;i<n;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);}
 vector<int> par(N,-1),ord,sz(N,1);ord.reserve(N);ord.push_back(0);
 for(int i=0;i<(int)ord.size();i++){int u=ord[i];for(int v:g[u])if(v!=par[u]){par[v]=u;ord.push_back(v);}}
 for(int i=N-1;i>0;i--)sz[par[ord[i]]]+=sz[ord[i]];
 long long best=-1,bestAfter=0;
 for(int u=0;u<N;u++){vector<long long> c;for(int v:g[u]){if(v==par[u])c.push_back(N-sz[u]);else c.push_back(sz[v]);}
  long long tot=N-1,sq=0;for(long long x:c)sq+=x*x;long long pairs=(tot*tot-sq)/2;
  sort(c.rbegin(),c.rend());long long red=c.size()>=2?c[0]*c[1]:0;
  if(pairs>best){best=pairs;bestAfter=pairs-red;}}
 printf("%lld %lld\n",best,bestAfter);}
