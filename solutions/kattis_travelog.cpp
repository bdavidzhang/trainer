#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,m,d; scanf("%d %d %d",&n,&m,&d);
    vector<array<int,3>> es(m);
    for(auto&e:es)scanf("%d %d %d",&e[0],&e[1],&e[2]);
    sort(es.begin(),es.end()); es.erase(unique(es.begin(),es.end()),es.end());
    vector<vector<pair<int,int>>> g(n+1);
    for(auto&e:es)g[e[0]].push_back({e[1],e[2]});
    vector<ll> T(d); for(auto&t:T)scanf("%lld",&t);
    sort(T.begin(),T.end());
    const ll INF=LLONG_MAX/4;
    vector<ll> dist(n+1,INF); dist[1]=0;
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq; pq.push({0,1});
    vector<int> order;
    while(!pq.empty()){
        auto [dd,u]=pq.top();pq.pop();
        if(dd!=dist[u])continue;
        order.push_back(u);
        for(auto [v,h]:g[u]) if(dd+h<dist[v]){dist[v]=dd+h;pq.push({dist[v],v});}
    }
    if(T.back()>dist[n]){puts("0");return 0;}
    vector<int> cnt(n+1,0),pre(n+1,0); cnt[1]=1;
    for(int u:order){
        if(!cnt[u])continue;
        auto it=upper_bound(T.begin(),T.end(),dist[u]);
        ll lim = it==T.end()?INF:*it;
        for(auto [v,h]:g[u]) if(dist[u]+h==dist[v] && dist[v]<=lim){
            cnt[v]=min(2,cnt[v]+cnt[u]); pre[v]=u;
        }
    }
    if(cnt[n]==0){puts("0");return 0;}
    if(cnt[n]>=2){puts("1");return 0;}
    vector<int> p; for(int v=n;v;v=pre[v])p.push_back(v);
    reverse(p.begin(),p.end());
    printf("%d\n",(int)p.size());
    for(int v:p)printf("%d\n",v);
}
