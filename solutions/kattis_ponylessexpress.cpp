#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=LLONG_MAX/4;
int n;ll C[205],D[205];vector<int> ch[205];int dep[205],mx[205];
vector<ll> f[205]; // f[v][t-dep[v]]
// Hungarian: min cost perfect matching on m x m matrix a (1-indexed)
ll hungarian(const vector<vector<ll>>&a,int m){
 vector<ll> u(m+1),v(m+1),minv(m+1);vector<int> p(m+1),way(m+1);vector<char> used(m+1);
 for(int i=1;i<=m;i++){p[0]=i;int j0=0;fill(minv.begin(),minv.end(),INF);fill(used.begin(),used.end(),0);
  do{used[j0]=1;int i0=p[j0],j1=0;ll delta=INF;
   for(int j=1;j<=m;j++)if(!used[j]){ll cur=a[i0][j]-u[i0]-v[j];if(cur<minv[j]){minv[j]=cur;way[j]=j0;}if(minv[j]<delta){delta=minv[j];j1=j;}}
   for(int j=0;j<=m;j++)if(used[j]){u[p[j]]+=delta;v[j]-=delta;}else minv[j]-=delta;
   j0=j1;}while(p[j0]!=0);
  do{int j1=way[j0];p[j0]=p[j1];j0=j1;}while(j0);}
 return -v[0];}
void solve(int v){
 int m=ch[v].size();
 for(int c:ch[v]){dep[c]=dep[v]+1;mx[c]=mx[v]+m;solve(c);}
 f[v].assign(mx[v]-dep[v]+1,0);
 vector<vector<ll>> a(m+1,vector<ll>(m+1));
 for(int t=dep[v];t<=mx[v];t++){
  ll own=v?C[v]*(D[v]-t)*(D[v]-t):0;ll best=0;
  if(m==1){best=f[ch[v][0]][t+1-dep[ch[v][0]]];}
  else if(m>1){for(int i=1;i<=m;i++){int c=ch[v][i-1];for(int k=1;k<=m;k++)a[i][k]=f[c][t+k-dep[c]];}best=hungarian(a,m);}
  f[v][t-dep[v]]=own+best;}
}
int main(){scanf("%d",&n);for(int i=1;i<=n;i++){int r;scanf("%lld %lld %d",&C[i],&D[i],&r);ch[r].push_back(i);}
 dep[0]=0;mx[0]=0;solve(0);printf("%lld\n",f[0][0]);}
