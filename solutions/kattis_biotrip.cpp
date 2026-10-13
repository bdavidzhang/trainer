#include <bits/stdc++.h>
using namespace std;
// State = directed road (u, k): having just travelled the k-th road of u, arriving at to[u][k].
int n,D,A1,A2;
vector<int> to[1005],tm_[1005],ang[1005],rev_[1005];
int base[1005];
int main(){
    scanf("%d %d %d %d",&n,&D,&A1,&A2);
    int S=0;
    for(int i=1;i<=n;i++){
        int m; scanf("%d",&m); base[i]=S; S+=m;
        to[i].resize(m);tm_[i].resize(m);ang[i].resize(m);rev_[i].assign(m,-1);
        for(int k=0;k<m;k++)scanf("%d %d %d",&to[i][k],&tm_[i][k],&ang[i][k]);
    }
    if(D==1){puts("0");return 0;}
    for(int i=1;i<=n;i++)for(size_t k=0;k<to[i].size();k++){
        int j=to[i][k];
        for(size_t q=0;q<to[j].size();q++) if(to[j][q]==i){rev_[i][k]=q;break;}
    }
    // transitions: state (u,k) arriving at v -> state (v,q), cost tm_[v][q]
    vector<vector<pair<int,int>>> fw(S),bw(S);
    for(int u=1;u<=n;u++)for(size_t k=0;k<to[u].size();k++){
        int v=to[u][k]; int s=base[u]+k;
        for(size_t q=0;q<to[v].size();q++){
            bool ok;
            if(v==1) ok=true;
            else if(rev_[u][k]<0) ok=false;
            else{
                int heading=(ang[v][rev_[u][k]]+180)%360;
                int left=((ang[v][q]-heading)%360+360)%360; // ccw turn amount in [0,360)
                int right=(360-left)%360;
                ok = (left<=A1) || (right<=A2);
            }
            if(ok){int t=base[v]+q; fw[s].push_back({t,tm_[v][q]}); bw[t].push_back({s,tm_[v][q]});}
        }
    }
    const int INF=1e9;
    auto dijk=[&](vector<int>&dist,vector<vector<pair<int,int>>>&g){
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        for(int s=0;s<S;s++) if(dist[s]<INF)pq.push({dist[s],s});
        while(!pq.empty()){
            auto [d,s]=pq.top();pq.pop();
            if(d>dist[s])continue;
            for(auto&e:g[s]) if(d+e.second<dist[e.first]){dist[e.first]=d+e.second;pq.push({dist[e.first],e.first});}
        }
    };
    vector<int> d1(S,INF),d2(S,INF);
    for(size_t k=0;k<to[1].size();k++)d1[base[1]+k]=tm_[1][k];
    dijk(d1,fw);
    for(int u=1;u<=n;u++)for(size_t k=0;k<to[u].size();k++) if(to[u][k]==1)d2[base[u]+k]=0;
    dijk(d2,bw);
    int ans=INF;
    for(int u=1;u<=n;u++)for(size_t k=0;k<to[u].size();k++) if(to[u][k]==D){
        int s=base[u]+k; if(d1[s]<INF&&d2[s]<INF)ans=min(ans,d1[s]+d2[s]);
    }
    if(ans>=INF)puts("impossible"); else printf("%d\n",ans);
}
