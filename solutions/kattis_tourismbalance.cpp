#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;ll k;
// ordered pairs i!=j with v_i - v_j = k in a sorted vector
ll cnt(vector<ll>&a){sort(a.begin(),a.end());ll r=0;size_t m=a.size();
  if(k==0){for(size_t i=0;i<m;){size_t j=i;while(j<m&&a[j]==a[i])j++;ll c=j-i;r+=c*(c-1);i=j;}return r;}
  size_t lo=0,hi=0;for(size_t i=0;i<m;i++){ll tg=a[i]-k;while(lo<m&&a[lo]<tg)lo++;while(hi<m&&a[hi]<=tg)hi++;r+=hi-lo;}return r;}
int main(){scanf("%d %lld",&n,&k);vector<ll>v(n);for(auto&x:v)scanf("%lld",&x);
  vector<vector<int>>g(n);vector<int>deg(n,0);
  for(int i=0;i<n;i++){int a,b;scanf("%d %d",&a,&b);a--;b--;g[a].push_back(b);g[b].push_back(a);deg[a]++;deg[b]++;}
  vector<char>off(n,0);vector<int>st;for(int i=0;i<n;i++)if(deg[i]==1)st.push_back(i);
  while(!st.empty()){int u=st.back();st.pop_back();off[u]=1;for(int w:g[u])if(!off[w]&&--deg[w]==1)st.push_back(w);}
  vector<ll>all(v);ll A=cnt(all),S=0;
  vector<char>vis(n,0);
  for(int c=0;c<n;c++)if(!off[c]){vector<ll>vals;vector<int>q{c};vis[c]=1;
    for(size_t h=0;h<q.size();h++){int u=q[h];vals.push_back(v[u]);for(int w:g[u])if(off[w]&&!vis[w]){vis[w]=1;q.push_back(w);}}
    S+=cnt(vals);}
  printf("%lld\n",2*A-S+(k==0?n:0));}
