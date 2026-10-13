#include <bits/stdc++.h>
using namespace std;
int n,m;vector<int>U,V;vector<long long>W;
vector<int> par;int fnd(int x){return par[x]==x?x:par[x]=fnd(par[x]);}
vector<vector<pair<int,int>>> adj;
vector<char> inT,inM;
bool dfs(int u,int target,int pe,vector<int>&path){
    if(u==target)return true;
    for(auto [v,e]:adj[u]){ if(e==pe||!inT[e])continue;
        path.push_back(e);
        if(dfs(v,target,e,path))return true;
        path.pop_back();}
    return false;
}
int main(){scanf("%d %d",&n,&m);U.resize(m);V.resize(m);W.resize(m);
    for(int i=0;i<m;i++){scanf("%d %d %lld",&U[i],&V[i],&W[i]);}
    vector<int> ord(m);iota(ord.begin(),ord.end(),0);
    stable_sort(ord.begin(),ord.end(),[&](int a,int b){return W[a]<W[b];}); // ties: lower index (tree edges) first
    par.resize(n+1);iota(par.begin(),par.end(),0);
    inT.assign(m,0);inM.assign(m,0);
    for(int e:ord){int a=fnd(U[e]),b=fnd(V[e]);if(a!=b){par[a]=b;inM[e]=1;}}
    adj.assign(n+1,{});
    for(int i=0;i<m;i++){adj[U[i]].push_back({V[i],i});adj[V[i]].push_back({U[i],i});}
    for(int i=0;i<n-1;i++)inT[i]=1;
    vector<pair<int,int>> res;
    for(int e=0;e<m;e++)if(inM[e]&&!inT[e]){
        vector<int> path;dfs(U[e],V[e],-1,path);
        int rem=-1;for(int f:path)if(!inM[f]){rem=f;break;}
        inT[rem]=0;inT[e]=1;res.push_back({rem+1,e+1});
    }
    printf("%d\n",(int)res.size());for(auto&p:res)printf("%d %d\n",p.first,p.second);}
