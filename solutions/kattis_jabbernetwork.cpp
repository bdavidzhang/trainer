#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
vector<int> adj[2005];
int comp[2005],par[2005];
ll W[2005],sub[2005],F[2005];
vector<int> ord;
int solveSide(int root,int label){
    ord.clear();ord.push_back(root);par[root]=0;comp[root]=label;
    for(size_t h=0;h<ord.size();h++){int u=ord[h];for(int w:adj[u])if(w!=par[u]){par[w]=u;comp[w]=label;ord.push_back(w);}}
    return 0;
}
int pick(int root){
    ord.clear();ord.push_back(root);
    for(size_t h=0;h<ord.size();h++){int u=ord[h];for(int w:adj[u])if(w!=par[u])ord.push_back(w);}
    ll tot=0,f0=0;
    for(int u:ord){sub[u]=W[u];tot+=W[u];}
    for(int i=(int)ord.size()-1;i>0;i--){int u=ord[i];sub[par[u]]+=sub[u];f0+=sub[u];}
    F[root]=f0;
    int best=-1;
    for(size_t i=0;i<ord.size();i++){int u=ord[i];if(i)F[u]=F[par[u]]+tot-2*sub[u];
        if((int)adj[u].size()<3){if(best<0||F[u]<F[best]||(F[u]==F[best]&&u<best))best=u;}}
    return best;
}
int main(){
    scanf("%d",&n);vector<pair<int,int>> E(n-1);
    for(auto&e:E){scanf("%d %d",&e.first,&e.second);adj[e.first].push_back(e.second);adj[e.second].push_back(e.first);}
    int d;scanf("%d",&d);vector<int> S(d),T(d);vector<ll> C(d);
    for(int i=0;i<d;i++)scanf("%d %d %lld",&S[i],&T[i],&C[i]);
    for(auto&e:E){int a=e.first,b=e.second;
        adj[a].erase(find(adj[a].begin(),adj[a].end(),b));adj[b].erase(find(adj[b].begin(),adj[b].end(),a));
        solveSide(a,0);solveSide(b,1);
        for(int i=1;i<=n;i++)W[i]=0;
        for(int i=0;i<d;i++)if(comp[S[i]]!=comp[T[i]]){W[S[i]]+=C[i];W[T[i]]+=C[i];}
        int u=pick(a),v=pick(b);
        if(u>v)swap(u,v);
        printf("%d %d\n",u,v);
        adj[u].push_back(v);adj[v].push_back(u);
    }
}
