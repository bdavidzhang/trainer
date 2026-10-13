#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N; vector<vector<ll>> D; vector<int> disc,low; int timer_; bool bad; ll lim;
void dfs(int u,int p){
    disc[u]=low[u]=++timer_;
    for(int v=0;v<N;v++){ if(v==u||D[u][v]>lim)continue;
        if(!disc[v]){ dfs(v,u); low[u]=min(low[u],low[v]); if(u!=0&&low[v]>=disc[u])bad=true; }
        else if(v!=p) low[u]=min(low[u],disc[v]);
    }
}
bool ok(ll d){
    lim=d; disc.assign(N,0); low.assign(N,0); timer_=0; bad=false;
    dfs(0,-1);
    if(timer_<N) return false;
    return !bad;
}
int main(){
    int n; scanf("%d",&n); N=n+1;
    vector<ll> x(N,0),y(N,0);
    for(int i=1;i<=n;i++)scanf("%lld %lld",&x[i],&y[i]);
    D.assign(N,vector<ll>(N,0));
    vector<ll> c;
    for(int i=0;i<N;i++)for(int j=i+1;j<N;j++){ll dx=x[i]-x[j],dy=y[i]-y[j];D[i][j]=D[j][i]=dx*dx+dy*dy;c.push_back(D[i][j]);}
    sort(c.begin(),c.end()); c.erase(unique(c.begin(),c.end()),c.end());
    int lo=0,hi=c.size()-1;
    while(lo<hi){int mid=(lo+hi)/2; if(ok(c[mid]))hi=mid; else lo=mid+1;}
    printf("%.10Lf\n",sqrtl((long double)c[lo]));
}
