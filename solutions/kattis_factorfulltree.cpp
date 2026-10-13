#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef __int128 lll;
int n; vector<int> adj[65], ch[65];
int par_[65], sz[65], ht[65];
void dfs(int u,int p){
    par_[u]=p; sz[u]=1; ht[u]=1;
    for(int v:adj[u]) if(v!=p){ ch[u].push_back(v); dfs(v,u); sz[u]+=sz[v]; ht[u]=max(ht[u],ht[v]+1); }
}
// mode 0: heavy child = deepest subtree, mode 1: largest subtree
// chains get distinct primes, longer chains get smaller primes; x_v = x_parent * prime(chain(v)),
// the root itself is 1 and its chain's prime is first applied at its heavy child.
bool build(int mode, vector<ull>&x){
    vector<int> heavy(n+1,0), head(n+1,0);
    for(int u=1;u<=n;u++){
        int b=0;
        for(int v:ch[u]){
            if(!b) b=v;
            else if(mode==0? ht[v]>ht[b] : sz[v]>sz[b]) b=v;
        }
        heavy[u]=b;
    }
    vector<int> heads; 
    vector<int> order; order.push_back(1);
    head[1]=1; heads.push_back(1);
    for(size_t i=0;i<order.size();i++){
        int u=order[i];
        for(int v:ch[u]){
            if(v==heavy[u]) head[v]=head[u]; else { head[v]=v; heads.push_back(v);} 
            order.push_back(v);
        }
    }
    vector<int> clen(n+1,0);
    for(int u=1;u<=n;u++) clen[head[u]]++;
    clen[1]--; // root contributes exponent 0
    sort(heads.begin(),heads.end(),[&](int a,int b){ if(clen[a]!=clen[b]) return clen[a]>clen[b]; return a<b;});
    vector<int> primes; for(int p=2;(int)primes.size()<(int)heads.size();p++){ bool ok=true; for(int q:primes) if(p%q==0){ok=false;break;} if(ok) primes.push_back(p);} 
    vector<int> pr(n+1,0);
    for(size_t i=0;i<heads.size();i++) pr[heads[i]]=primes[i];
    x.assign(n+1,0); x[1]=1;
    const lll LIM=(lll)1000000000000000000LL;
    for(size_t i=1;i<order.size();i++){
        int u=order[i];
        lll v=(lll)x[par_[u]]*pr[head[u]];
        if(v>LIM) return false;
        x[u]=(ull)v;
    }
    return true;
}
int main(){
    if(scanf("%d",&n)!=1) return 0;
    for(int i=0;i<n-1;i++){int u,v;scanf("%d %d",&u,&v);adj[u].push_back(v);adj[v].push_back(u);}
    dfs(1,0);
    vector<ull> x;
    if(!build(0,x)) if(!build(1,x)) { fprintf(stderr,"FAIL\n"); }
    for(int i=1;i<=n;i++) printf("%llu%c",x[i],i==n?'\n':' ');
}
