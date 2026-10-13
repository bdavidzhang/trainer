#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,k;vector<vector<int>> g;
vector<int> bfs(int s){vector<int> d(n+1,-1);d[s]=0;vector<int> q{s};for(size_t h=0;h<q.size();h++){int u=q[h];for(int v:g[u])if(d[v]<0){d[v]=d[u]+1;q.push_back(v);}}return d;}
int main(){scanf("%d %d %d",&n,&m,&k);vector<int> w(k);for(int&x:w)scanf("%d",&x);g.resize(n+1);
for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);}
auto d1=bfs(1),dn=bfs(n);ll S=0;for(int x:w)S+=dn[x];
ll num=(ll)d1[n]*(k-1),den=k-1;
for(int x:w){ll c=(ll)d1[x]*(k-1)+S-dn[x];num=min(num,c);}
ll gg=std::gcd(num,den);printf("%lld/%lld\n",num/gg,den/gg);}
