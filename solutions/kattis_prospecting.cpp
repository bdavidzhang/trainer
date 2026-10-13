#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=(ll)4e15;
int n;vector<int> par,dsu;vector<ll> X,Y,nd,dl;vector<int> ver;
int fnd(int x){while(dsu[x]!=x){dsu[x]=dsu[dsu[x]];x=dsu[x];}return x;}
struct It{ll n,d;int v,ver;};
// returns true if a has lower priority than b (for max-heap)
struct Cmp{bool operator()(const It&a,const It&b)const{
  bool pa=a.d>=0,pb=b.d>=0;
  if(pa!=pb)return pb;
  if(pa){return a.n>b.n;}
  return a.n+a.d<b.n+b.d;}};
int main(){scanf("%d",&n);par.assign(n,0);X.assign(n,0);Y.assign(n,0);int ml=-1;
 for(int i=1;i<n;i++){int p;ll x,y;scanf("%d %lld %lld",&p,&x,&y);par[i]=p;X[i]=x;Y[i]=y;if(x<0)ml=i;}
 // worst case
 vector<ll> f(n,0);
 for(int i=n-1;i>=1;i--){ll opt=Y[i]-1;if(i!=ml){ll g=f[i]+Y[i]-X[i];if(g>opt)opt=g;}f[par[i]]+=opt;}
 ll a=f[0]+1;
 // best case
 nd.assign(n,0);dl.assign(n,0);ver.assign(n,0);dsu.resize(n);
 priority_queue<It,vector<It>,Cmp> pq;
 for(int i=0;i<n;i++)dsu[i]=i;
 for(int i=1;i<n;i++){if(i==ml){nd[i]=Y[i]-1;dl[i]=INF;}else{nd[i]=Y[i]-(X[i]>0?1:0);dl[i]=X[i]-Y[i];}pq.push({nd[i],dl[i],i,0});}
 ll cur=0,need=0;
 while(!pq.empty()){It t=pq.top();pq.pop();int v=t.v;if(fnd(v)!=v||ver[v]!=t.ver)continue;
  int p=fnd(par[v]);
  if(p==0){if(nd[v]-cur>need)need=nd[v]-cur;cur+=dl[v];if(cur>=INF/2)break;dsu[v]=0;}
  else{nd[p]=max(nd[p],nd[v]-dl[p]);dl[p]+=dl[v];if(dl[p]>INF)dl[p]=INF;dsu[v]=p;ver[p]++;pq.push({nd[p],dl[p],p,ver[p]});}
 }
 printf("%lld %lld\n",a,need+1);}
