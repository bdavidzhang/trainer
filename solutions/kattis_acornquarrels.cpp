#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
vector<vector<int>> adj, F; // F sorted
vector<int> par_, off_;
int fnd(int x){ // weighted dsu: d[x] = d[root] + off_[x]
    if(par_[x]==x)return x;
    int r=fnd(par_[x]);
    off_[x]+=off_[par_[x]];par_[x]=r;return r;
}
// offset of w's value as seen at time u
int offs(int w,int u){
    int c=lower_bound(F[w].begin(),F[w].end(),u)-F[w].begin();
    return (w<u?(int)F[w].size():0)-c;
}
int main(){
    scanf("%d",&n);
    adj.assign(n+1,{});F.assign(n+1,{});
    for(int i=0;i<n-1;i++){int u,v;scanf("%d %d",&u,&v);adj[u].push_back(v);adj[v].push_back(u);}
    vector<int> order,par(n+1,0);order.reserve(n);
    order.push_back(1);
    for(int i=0;i<(int)order.size();i++){int v=order[i];for(int w:adj[v])if(w!=par[v]){par[w]=v;order.push_back(w);}}
    vector<char> cov(n+1,0);
    for(int i=n-1;i>=0;i--){
        int v=order[i];
        for(int w:adj[v])if(w!=par[v]&&!cov[w]){F[v].push_back(w);F[w].push_back(v);cov[w]=1;cov[v]=1;}
    }
    if(!cov[1]){int c=adj[1][0];F[1].push_back(c);F[c].push_back(1);}
    for(int v=1;v<=n;v++)sort(F[v].begin(),F[v].end());
    par_.resize(n+1);off_.assign(n+1,0);iota(par_.begin(),par_.end(),0);
    // equalities
    for(int u=1;u<=n;u++){
        int f0=F[u][0];
        for(size_t k=1;k<F[u].size();k++){
            int f=F[u][k];
            // d_f + offs(f,u) = d_f0 + offs(f0,u)
            int delta=offs(f0,u)-offs(f,u); // d_f = d_f0 + delta
            int rf=fnd(f),r0=fnd(f0);
            if(rf==r0){ if(off_[f]!=off_[f0]+delta){fprintf(stderr,"EQ CONFLICT\n");return 1;} }
            else { // d_f = d_rf + off_[f]; d_f0 = d_r0 + off_[f0]; d_rf = d_r0 + off_[f0]+delta-off_[f]
                par_[rf]=r0;off_[rf]=off_[f0]+delta-off_[f];
            }
        }
    }
    // inequalities: d_x >= d_w + c  => edge w->x with weight c (on roots)
    vector<vector<pair<int,int>>> g(n+1);
    vector<int> indeg(n+1,0);
    for(int u=1;u<=n;u++){
        int f0=F[u][0];
        for(int w:adj[u]){
            if(binary_search(F[u].begin(),F[u].end(),w))continue;
            // d_f0 + offs(f0,u) >= d_w + offs(w,u) + 1
            int c=offs(w,u)+1-offs(f0,u);
            int rx=fnd(f0),rw=fnd(w);
            // d_rx + off[f0] >= d_rw + off[w] + c
            c+=off_[w]-off_[f0];
            if(rx==rw){ if(c>0){fprintf(stderr,"SELF CONFLICT\n");return 1;} continue; }
            g[rw].push_back({rx,c});indeg[rx]++;
        }
    }
    const ll NEG=LLONG_MIN/4;
    vector<ll> val(n+1,NEG);
    vector<int> q;
    for(int v=1;v<=n;v++)if(fnd(v)==v&&indeg[v]==0)q.push_back(v);
    int cnt=0,roots=0;
    for(int v=1;v<=n;v++)if(fnd(v)==v)roots++;
    for(size_t i=0;i<q.size();i++){
        int v=q[i];cnt++;
        if(val[v]==NEG)val[v]=0;
        for(auto [x,c]:g[v]){val[x]=max(val[x],val[v]+c);if(--indeg[x]==0)q.push_back(x);}
    }
    if(cnt!=roots){fprintf(stderr,"CYCLE\n");return 1;}
    vector<ll> d(n+1);ll mn=LLONG_MAX,mx=LLONG_MIN;
    for(int v=1;v<=n;v++){int r=fnd(v);d[v]=val[r]+off_[v];mn=min(mn,d[v]);mx=max(mx,d[v]);}
    if(mx-mn>n-1){fprintf(stderr,"RANGE %lld > %d\n",mx-mn,n-1);}
    for(int v=1;v<=n;v++)printf("%lld%c",d[v]-mn+n,v==n?'\n':' ');
}
