#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,m;ll k;scanf("%d %d %lld",&n,&m,&k);
    vector<vector<pair<int,int>>> g(n);
    vector<int> ws={0};
    for(int i=0;i<m;i++){int u,v,w;scanf("%d %d %d",&u,&v,&w);g[u].push_back({v,w});ws.push_back(w);}
    sort(ws.begin(),ws.end());ws.erase(unique(ws.begin(),ws.end()),ws.end());
    ll best=LLONG_MAX;
    vector<ll> dist(n);
    for(int T:ws){
        fill(dist.begin(),dist.end(),LLONG_MAX);
        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
        dist[0]=0;pq.push({0,0});
        while(!pq.empty()){
            auto [d,u]=pq.top();pq.pop();
            if(d>dist[u])continue;
            if(u==n-1)break;
            for(auto [v,w]:g[u]){
                ll nd=d+max(w,T);
                if(nd<dist[v]){dist[v]=nd;pq.push({nd,v});}
            }
        }
        best=min(best,dist[n-1]-k*T);
    }
    printf("%lld\n",max(0LL,best));
}
