#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,k;
vector<vector<pair<int,int>>> g;
vector<ll> dij(int s){
    vector<ll> d(n+1,LLONG_MAX);
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    d[s]=0; pq.push({0,s});
    while(!pq.empty()){
        auto [dd,u]=pq.top(); pq.pop();
        if(dd>d[u]) continue;
        for(auto [v,w]:g[u]) if(dd+w<d[v]){ d[v]=dd+w; pq.push({d[v],v}); }
    }
    return d;
}
int main(){
    scanf("%d %d %d",&n,&m,&k);
    g.resize(n+1);
    for(int i=0;i<m;i++){ int a,b,l; scanf("%d %d %d",&a,&b,&l); g[a].push_back({b,l}); g[b].push_back({a,l}); }
    auto d1=dij(1), dn=dij(n);
    vector<pair<ll,int>> st; // (dist, prob in 1e-4 units)
    bool sure=false;
    for(int i=0;i<k;i++){
        int v; char buf[64]; scanf("%d %63s",&v,buf);
        double p=atof(buf); int pi=(int)llround(p*10000);
        if(pi>=10000) sure=true;
        st.push_back({d1[v]+dn[v],pi});
    }
    if(!sure){ puts("impossible"); return 0; }
    sort(st.begin(),st.end());
    long double rem=1, ans=0;
    for(auto&[d,pi]:st){
        long double p=pi/10000.0L;
        ans+=rem*p*d; rem*=(1-p);
        if(pi>=10000) break;
    }
    printf("%.9Lf\n",ans);
}
