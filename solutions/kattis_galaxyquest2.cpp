#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m,q;
    scanf("%d %d %d",&n,&m,&q);
    vector<array<double,3>> p(n);
    for(auto&v:p)scanf("%lf %lf %lf",&v[0],&v[1],&v[2]);
    vector<vector<pair<int,double>>> g(n);
    for(int i=0;i<m;i++){
        int a,b;scanf("%d %d",&a,&b);a--;b--;
        double d=0;
        for(int k=0;k<3;k++)d+=(p[a][k]-p[b][k])*(p[a][k]-p[b][k]);
        double w=sqrt(sqrt(d)); // sqrt of length
        g[a].push_back({b,w});g[b].push_back({a,w});
    }
    vector<double> dist(n,1e18);
    priority_queue<pair<double,int>,vector<pair<double,int>>,greater<>> pq;
    dist[0]=0;pq.push({0,0});
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:g[u])if(d+w<dist[v]){dist[v]=d+w;pq.push({dist[v],v});}
    }
    while(q--){
        int c;double t;scanf("%d %lf",&c,&t);c--;
        double S=dist[c];
        if(S>1e17||2*S>t){puts("impossible");continue;}
        double r=sqrt(max(0.0,t*t-4*S*S));
        printf("%.10f\n",4*S*S/(t+r));
    }
}
