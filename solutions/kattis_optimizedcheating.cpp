#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n,m,k;scanf("%d %d %d",&n,&m,&k);vector<ll>a(n);for(auto&x:a)scanf("%lld",&x);
 unordered_set<ll>bad;for(int i=0;i<n;i++)if(i!=k-1)bad.insert(a[i]);
 vector<char>op(m);vector<ll>v(m);for(int i=0;i<m;i++)scanf(" %c %lld",&op[i],&v[i]);
 ll st=a[k-1];if(!bad.count(st)){puts("0");return 0;}
 // BFS only through "bad" values (<=1e9); any non-bad value is a goal
 vector<ll>val{st};vector<int>par{-1},pop{-1};unordered_set<ll>seen{st};
 for(size_t h=0;h<val.size();h++){ll u=val[h];
  for(int i=0;i<m;i++){ll w;if(op[i]=='+')w=u+v[i];else if(op[i]=='-')w=u-v[i];else if(op[i]=='*')w=u*v[i];else w=u/v[i];
   if(w<0)continue;
   if(!bad.count(w)){vector<int>res{i+1};for(int x=h;par[x]>=0;x=par[x])res.push_back(pop[x]+1);reverse(res.begin(),res.end());printf("%d\n",(int)res.size());for(int x:res)printf("%d\n",x);return 0;}
   if(seen.insert(w).second){val.push_back(w);par.push_back(h);pop.push_back(i);}}}
 puts("-1");}
