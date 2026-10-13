#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n; scanf("%d",&n);
    vector<ll> t(n);
    for(auto&x:t)scanf("%lld",&x);
    vector<vector<pair<int,int>>> g(n);
    for(int i=0;i<n-1;i++){int u,v,w;scanf("%d %d %d",&u,&v,&w);u--;v--;g[u].push_back({v,w});g[v].push_back({u,w});}
    vector<int> par(n,-1),order; vector<ll> pw(n,0);
    order.reserve(n); order.push_back(0);
    for(int i=0;i<(int)order.size();i++){int u=order[i];for(auto[v,w]:g[u])if(v!=par[u]){par[v]=u;pw[v]=w;order.push_back(v);}}
    vector<ll> cnt(n,1),st(t),D(n,0),T(n,0); // D: sum dist in subtree, T: sum t_v*dist
    ll totT=0; for(ll x:t) totT+=x;
    for(int i=n-1;i>0;i--){int u=order[i],p=par[u];
        D[p]+=D[u]+pw[u]*cnt[u]; T[p]+=T[u]+pw[u]*st[u]; cnt[p]+=cnt[u]; st[p]+=st[u];}
    vector<ll> AD(n),AT(n); AD[0]=D[0];AT[0]=T[0];
    for(int i=1;i<n;i++){int u=order[i],p=par[u];
        AD[u]=AD[p]+pw[u]*(n-2*cnt[u]);
        AT[u]=AT[p]+pw[u]*(totT-2*st[u]);}
    for(int i=0;i<n;i++) printf("%lld\n", t[i]*AD[i]+AT[i]);
}
