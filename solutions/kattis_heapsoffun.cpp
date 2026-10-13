#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
ll pw(ll a,ll e){ ll r=1; a%=MOD; while(e){ if(e&1) r=r*a%MOD; a=a*a%MOD; e>>=1;} return r; }
ll ev(const vector<ll>&p, ll x){ ll r=0; for(int i=(int)p.size()-1;i>=0;i--) r=(r*x+p[i])%MOD; return r; }
int main(){
    int n; scanf("%d",&n);
    vector<ll> b(n+1); vector<int> par(n+1); vector<vector<int>> ch(n+1);
    int root=0;
    for(int i=1;i<=n;i++){ scanf("%lld %d",&b[i],&par[i]); if(par[i]==0) root=i; else ch[par[i]].push_back(i); }
    vector<ll> c(b.begin()+1,b.end()); c.push_back(0);
    sort(c.begin(),c.end()); c.erase(unique(c.begin(),c.end()),c.end());
    vector<ll> inv(n+3); for(int i=1;i<n+3;i++) inv[i]=pw(i,MOD-2);
    vector<int> order{root};
    for(size_t i=0;i<order.size();i++) for(int u:ch[order[i]]) order.push_back(u);
    vector<ll> mn(n+1);
    vector<vector<vector<ll>>> F(n+1);
    for(int oi=n-1;oi>=0;oi--){
        int v=order[oi];
        mn[v]=b[v];
        for(int u:ch[v]) mn[v]=min(mn[v],mn[u]);
        int K=lower_bound(c.begin(),c.end(),mn[v])-c.begin();
        vector<vector<ll>> H(K+1);
        for(int j=1;j<=K;j++){
            vector<ll> g{1};
            for(int u:ch[v]){
                const vector<ll>&f=F[u][j];
                vector<ll> ng(g.size()+f.size()-1,0);
                for(size_t x=0;x<g.size();x++) if(g[x]) for(size_t y=0;y<f.size();y++) ng[x+y]=(ng[x+y]+g[x]*f[y])%MOD;
                g.swap(ng);
            }
            vector<ll> h(g.size()+1,0);
            for(size_t x=0;x<g.size();x++) h[x+1]=g[x]*inv[x+1]%MOD;
            H[j]=h;
        }
        for(int u:ch[v]){ F[u].clear(); F[u].shrink_to_fit(); }
        F[v].assign(K+1,{});
        ll suf=0, ib=pw(b[v],MOD-2);
        for(int j=K;j>=1;j--){
            ll hi=ev(H[j],c[j]%MOD), lo=ev(H[j],c[j-1]%MOD);
            vector<ll> f(H[j].size());
            for(size_t x=0;x<f.size();x++) f[x]=(MOD-H[j][x])%MOD;
            f[0]=(f[0]+hi+suf)%MOD;
            for(auto&x:f) x=x*ib%MOD;
            F[v][j]=f;
            suf=(suf+hi-lo+MOD)%MOD;
        }
    }
    printf("%lld\n",ev(F[root][1],0));
}
