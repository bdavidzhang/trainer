#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=(ll)1e15;
int n,m;
vector<vector<pair<int,int>>> adj;
vector<int> par,pe,tin,ord;
vector<char> cov;
vector<vector<vector<int>>> cycAt;
vector<array<array<ll,2>,2>> f;
static inline ll best(int c,int t){return min(f[c][t][0],f[c][t][1]);}
int main(){
    scanf("%d %d",&n,&m);
    adj.resize(n+1); vector<int> ea(m),eb(m);
    for(int i=0;i<m;i++){scanf("%d %d",&ea[i],&eb[i]);adj[ea[i]].push_back({eb[i],i});adj[eb[i]].push_back({ea[i],i});}
    par.assign(n+1,0);pe.assign(n+1,-1);tin.assign(n+1,-1);cov.assign(n+1,0);
    cycAt.resize(n+1); f.resize(n+1);
    vector<int> roots; int timer=0;
    vector<int> itx(n+1,0);
    for(int r=1;r<=n;r++) if(tin[r]<0){
        roots.push_back(r);
        vector<int> st; st.push_back(r); tin[r]=timer++; ord.push_back(r);
        while(!st.empty()){
            int v=st.back();
            if(itx[v]<(int)adj[v].size()){
                auto [to,id]=adj[v][itx[v]++];
                if(tin[to]<0){tin[to]=timer++;par[to]=v;pe[to]=id;ord.push_back(to);st.push_back(to);}
            }else st.pop_back();
        }
    }
    for(int i=0;i<m;i++){
        int u=ea[i],w=eb[i];
        if(pe[u]==i||pe[w]==i) continue;
        if(tin[u]<tin[w]) swap(u,w); // w ancestor of u
        vector<int> cyc;
        for(int x=u;x!=w;x=par[x]){
            if(cov[x]){puts("-1");return 0;}
            cov[x]=1; cyc.push_back(x);
        }
        cycAt[w].push_back(std::move(cyc));
    }
    vector<vector<int>> bridgeKids(n+1);
    for(int v=1;v<=n;v++) if(par[v]&&!cov[v]) bridgeKids[par[v]].push_back(v);
    for(int idx=n-1;idx>=0;idx--){
        int v=ord[idx];
        ll sum[2]={0,0}; int cntInf[2]={0,0}; ll infG1[2]={INF,INF}; ll delta[2]={INF,INF};
        auto addBlock=[&](ll g[2][2]){
            for(int t=0;t<2;t++){
                if(g[t][0]>=INF){cntInf[t]++; infG1[t]=g[t][1];}
                else{sum[t]+=g[t][0]; if(g[t][1]<INF) delta[t]=min(delta[t],g[t][1]-g[t][0]);}
            }
        };
        for(int c:bridgeKids[v]){
            ll g[2][2];
            ll two=min(f[c][0][0],f[c][1][0]); two = two>=INF?INF:two+2;
            for(int t=0;t<2;t++){
                ll b=best(c,t); g[t][0]= b>=INF?INF:b+t;
                g[t][1]=two;
            }
            addBlock(g);
        }
        for(auto&cyc:cycAt[v]){
            ll g[2][2]={{INF,INF},{INF,INF}};
            int k=cyc.size();
            for(int a0=0;a0<3;a0++){
                ll dp[3][2],nd[3][2];
                for(int a=0;a<3;a++)for(int p=0;p<2;p++)dp[a][p]=INF;
                dp[a0][a0==1]=a0;
                for(int i=0;i<k;i++){
                    int c=cyc[i];
                    for(int a=0;a<3;a++)for(int p=0;p<2;p++)nd[a][p]=INF;
                    for(int a=0;a<3;a++)for(int b=0;b<3;b++){
                        ll vc;
                        if(a==2&&b==2) continue;
                        else if(a==2) vc=f[c][b][0];
                        else if(b==2) vc=f[c][a][0];
                        else if(a!=b) continue;
                        else vc=best(c,a);
                        if(vc>=INF) continue;
                        for(int p=0;p<2;p++) if(dp[a][p]<INF){
                            int np=p^(b==1);
                            nd[b][np]=min(nd[b][np],dp[a][p]+vc+b);
                        }
                    }
                    memcpy(dp,nd,sizeof(dp));
                }
                for(int b=0;b<3;b++){
                    ll val=dp[b][1]; if(val>=INF) continue;
                    if(a0==2&&b==2) continue;
                    if(a0==2) g[b][1]=min(g[b][1],val);
                    else if(b==2) g[a0][1]=min(g[a0][1],val);
                    else if(a0==b) g[a0][0]=min(g[a0][0],val);
                }
            }
            addBlock(g);
        }
        for(int t=0;t<2;t++){
            if(cntInf[t]==0){f[v][t][0]=sum[t]; f[v][t][1]= delta[t]>=INF?INF:sum[t]+delta[t];}
            else if(cntInf[t]==1){f[v][t][0]=INF; f[v][t][1]= infG1[t]>=INF?INF:sum[t]+infG1[t];}
            else f[v][t][0]=f[v][t][1]=INF;
        }
    }
    ll ans=0;
    for(int r:roots){
        ll b=min(best(r,0),best(r,1));
        if(b>=INF){puts("-1");return 0;}
        ans+=b;
    }
    printf("%lld\n",ans);
}
