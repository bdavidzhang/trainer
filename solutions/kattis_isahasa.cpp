#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;cin>>n>>m;map<string,int> id;vector<vector<pair<int,int>>> g;
 auto get=[&](const string&s){auto it=id.find(s);if(it!=id.end())return it->second;int k=id.size();id[s]=k;g.emplace_back();return k;};
 for(int i=0;i<n;i++){string a,r,b;cin>>a>>r>>b;int x=get(a),y=get(b);g[x].push_back({y,r=="has-a"});}
 int N=id.size();vector<vector<char>> reach(N,vector<char>(2*N,0));
 for(int s=0;s<N;s++){auto&R=reach[s];vector<int> q;R[2*s]=1;q.push_back(2*s);
  for(size_t i=0;i<q.size();i++){int u=q[i]/2,h=q[i]%2;for(auto&e:g[u]){int nh=h|e.second;int t=2*e.first+nh;if(!R[t]){R[t]=1;q.push_back(t);}}}}
 for(int i=1;i<=m;i++){string a,r,b;cin>>a>>r>>b;bool ans=false;
  if(id.count(a)&&id.count(b)){int x=id[a],y=id[b];ans=reach[x][2*y+(r=="has-a")];}
  else if(a==b&&r=="is-a")ans=true;
  printf("Query %d: %s\n",i,ans?"true":"false");}
}
