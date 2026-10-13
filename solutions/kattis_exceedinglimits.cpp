#include <bits/stdc++.h>
using namespace std;
int n,m; double T;
vector<vector<array<int,3>>> g;
vector<double> dist_;
bool ok(double x){
    fill(dist_.begin(),dist_.end(),1e300);
    priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> pq;
    dist_[0]=0; pq.push({0,0});
    while(!pq.empty()){
        auto [d,u]=pq.top(); pq.pop();
        if(d>dist_[u]) continue;
        if(d>T) return false;
        if(u==n-1) return true;
        for(auto&e:g[u]){
            double nd=d+e[1]/(e[2]+x);
            if(nd<dist_[e[0]]){ dist_[e[0]]=nd; pq.push({nd,e[0]}); }
        }
    }
    return dist_[n-1]<=T;
}
int main(){
    int t; scanf("%d %d %d",&n,&m,&t); T=t;
    g.resize(n); dist_.resize(n);
    for(int i=0;i<m;i++){int a,b,l,v; scanf("%d %d %d %d",&a,&b,&l,&v); a--;b--; g[a].push_back({b,l,v}); g[b].push_back({a,l,v});}
    if(ok(0)){ puts("0"); return 0; }
    double lo=0,hi=2e9;
    for(int it=0;it<70;it++){
        double mid=(lo+hi)/2;
        if(ok(mid)) hi=mid; else lo=mid;
    }
    printf("%.9f\n",hi);
}
