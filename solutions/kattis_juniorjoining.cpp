#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;scanf("%d",&n);map<int,vector<ll>>g;ll base=0;
for(int i=0;i<2*n;i++){int d,a,c;scanf("%d %d %d",&d,&a,&c);base+=a;g[c].push_back((ll)d-a);}
vector<ll>mg;mg.reserve(2*n);
for(auto&kv:g){auto&v=kv.second;sort(v.rbegin(),v.rend());int m=v.size();ll c=kv.first;
  for(int s=0;s<m;s++){ll bon=c*(min(s+1,m-s-1)-min(s,m-s));mg.push_back(v[s]+bon);}}
sort(mg.rbegin(),mg.rend());for(int i=0;i<n;i++)base+=mg[i];printf("%lld\n",base);}
