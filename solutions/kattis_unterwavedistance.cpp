#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;vector<ll> g;vector<int> ty;vector<vector<int>> adj;
vector<pair<ll,int>> arr[2];vector<int> stamp;
ll cube(ll x){return x*x*x;}
ll best;
void query(ll v,int t,int st){ // node of type t with value v, vs unmarked nodes of other type
 auto&a=arr[1-t];int pos=lower_bound(a.begin(),a.end(),make_pair(v,INT_MIN))-a.begin();
 for(int i=pos;i<(int)a.size();i++){if(stamp[a[i].second]==st)continue;best=min(best,llabs(cube(a[i].first)-cube(v)));break;}
 for(int i=pos-1;i>=0;i--){if(stamp[a[i].second]==st)continue;best=min(best,llabs(cube(a[i].first)-cube(v)));break;}
}
int main(){scanf("%d",&n);g.resize(n);ty.resize(n);adj.resize(n);stamp.assign(n,-1);
 for(int i=0;i<n;i++){char c;scanf("%lld %c",&g[i],&c);ty[i]=(c=='h');arr[ty[i]].push_back({g[i],i});}
 sort(arr[0].begin(),arr[0].end());sort(arr[1].begin(),arr[1].end());
 int e;scanf("%d",&e);for(int i=0;i<e;i++){int a,b;scanf("%d %d",&a,&b);a--;b--;adj[a].push_back(b);adj[b].push_back(a);}
 best=LLONG_MAX;
 for(int i=0;i<n;i++)query(g[i],ty[i],-2);
 vector<pair<ll,int>> ch;
 for(int x=0;x<n;x++){ch.clear();stamp[x]=x;ch.push_back({g[x]-1,ty[x]});
  for(int y:adj[x]){stamp[y]=x;ch.push_back({g[y]+1,ty[y]});}
  for(auto&c:ch)query(c.first,c.second,x);
  for(size_t i=0;i<ch.size();i++)for(size_t j=i+1;j<ch.size();j++)if(ch[i].second!=ch[j].second)best=min(best,llabs(cube(ch[i].first)-cube(ch[j].first)));
 }
 printf("%lld\n",best);}
