#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n,m;scanf("%d %d",&n,&m);int s,t;ll c;scanf("%d %d %lld",&s,&t,&c);
vector<vector<pair<int,int>>> g(n+1);
for(int i=0;i<m;i++){int u,v,p;scanf("%d %d %d",&u,&v,&p);g[u].push_back({v,p});g[v].push_back({u,p});}
vector<ll> d(n+1,-1);priority_queue<pair<ll,int>> pq;d[s]=c;pq.push({c,s});
while(!pq.empty()){auto [x,u]=pq.top();pq.pop();if(x<d[u])continue;
for(auto [v,p]:g[u]){ll y=x-(x*p+99)/100;if(y>d[v]){d[v]=y;pq.push({y,v});}}}
printf("%lld\n",d[t]);}
