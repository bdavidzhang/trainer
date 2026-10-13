#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n; ll K; scanf("%d %lld",&n,&K);
    vector<ll> w(n+1);
    for(int i=1;i<=n;i++)scanf("%lld",&w[i]);
    vector<vector<int>> g(n+1);
    for(int i=0;i<n-1;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);}
    vector<int> par(n+1,0),ord; ord.reserve(n); ord.push_back(1);
    for(int i=0;i<(int)ord.size();i++){int v=ord[i];for(int c:g[v])if(c!=par[v]){par[c]=v;ord.push_back(c);}}
    vector<ll> res(n+1,K);
    ll total=0;
    for(int v=1;v<=n;v++)if(w[v]>=0){res[v]-=w[v]; if(par[v])res[par[v]]-=w[v]; total+=w[v];}
    for(int v=1;v<=n;v++)if(res[v]<0){puts("-1");return 0;}
    for(int i=n-1;i>=0;i--){
        int v=ord[i];
        if(w[v]>=0)continue;
        ll x=res[v]; if(par[v])x=min(x,res[par[v]]);
        res[v]-=x; if(par[v])res[par[v]]-=x; total+=x;
    }
    printf("%lld\n",total);
}
