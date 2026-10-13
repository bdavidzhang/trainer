#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<pair<int,int>>> g;
vector<vector<int>> adj;
vector<int> mt; vector<char> vis;
bool tryk(int u){
    for(int v:adj[u]) if(!vis[v]){
        vis[v]=1;
        if(mt[v]<0||tryk(mt[v])){mt[v]=u;return true;}
    }
    return false;
}
int par[16],ed[16],vc[16];
int fnd(int x){return par[x]==x?x:par[x]=fnd(par[x]);}
bool ok(int a,int b){
    for(int i=1;i<=15;i++){par[i]=i;ed[i]=0;vc[i]=1;}
    for(int t=0;t<2;t++) for(auto&e:g[t?b:a]){
        int x=fnd(e.first),y=fnd(e.second);
        if(x!=y){par[x]=y;ed[y]+=ed[x];vc[y]+=vc[x];}
        if(++ed[y]>vc[y]) return false;
    }
    return true;
}
int main(){
    scanf("%d",&n); g.resize(n);
    for(int i=0;i<n;i++){int k;scanf("%d",&k);g[i].resize(k);for(auto&e:g[i])scanf("%d %d",&e.first,&e.second);}
    adj.assign(n,{});
    for(int i=0;i<n;i++) if(g[i].size()<=7) for(int j=0;j<n;j++) if(g[i].size()+g[j].size()==15 && ok(i,j)) adj[i].push_back(j);
    mt.assign(n,-1); int res=0;
    for(int i=0;i<n;i++) if(!adj[i].empty()){vis.assign(n,0); if(tryk(i))res++;}
    printf("%d\n",res);
}
