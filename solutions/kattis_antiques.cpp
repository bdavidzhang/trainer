#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,m,k;scanf("%d %d %d",&n,&m,&k);
    vector<ll> adj(m,0),w(m,0);vector<bool> forced(m,false);ll base=0;
    for(int i=0;i<n;i++){int a,b;ll p,q;scanf("%d %lld %d %lld",&a,&p,&b,&q);a--;b--;
        base+=min(p,q);
        if(a==b){forced[a]=true;continue;}
        adj[a]|=1LL<<b;adj[b]|=1LL<<a;
        if(p<q)w[a]+=q-p;else w[b]+=p-q; // dropping the cheaper shop costs the difference
    }
    int need=m-k; // independent set (unvisited shops) of size exactly need
    if(need<=0){printf("%lld\n",base);return 0;}
    int nb=m/2,na=m-nb; // A = vertices [0,na), B = [na,m)
    const ll INF=LLONG_MAX/4;
    int FB=1<<nb;
    vector<vector<ll>> g(nb+1,vector<ll>(FB,INF)); // g[j][mask]
    for(int mk=0;mk<FB;mk++)g[0][mk]=0;
    for(int mk=1;mk<FB;mk++){
        int v=__builtin_ctz(mk);int rest=mk&(mk-1);
        int gv=na+v;
        int rest2=rest&~(int)(adj[gv]>>na);
        for(int j=1;j<=nb;j++){
            ll val=g[j][rest];
            if(!forced[gv]&&g[j-1][rest2]<INF)val=min(val,g[j-1][rest2]+w[gv]);
            g[j][mk]=val;
        }
    }
    int FA=1<<na;ll maskA=(1LL<<na)-1;
    vector<char> ok(FA);vector<ll> wa(FA);vector<int> nbm(FA);
    ok[0]=1;wa[0]=0;nbm[0]=0;ll best=INF;
    for(int mk=0;mk<FA;mk++){
        if(mk){int v=__builtin_ctz(mk);int rest=mk&(mk-1);
            ok[mk]=ok[rest]&&!forced[v]&&!((adj[v]&maskA)&rest);
            wa[mk]=wa[rest]+w[v];nbm[mk]=nbm[rest]|(int)(adj[v]>>na);}
        if(!ok[mk])continue;
        int j=need-__builtin_popcount(mk);
        if(j<0||j>nb)continue;
        ll x=g[j][(FB-1)&~nbm[mk]];
        if(x<INF)best=min(best,x+wa[mk]);
    }
    if(best>=INF)puts("-1");else printf("%lld\n",base+best);
}
