#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> U,V,H;
vector<vector<int>> adj;
static bool valid(const vector<int>& st){
    vector<int> tmp;
    for(int v=1;v<=n;v++){
        tmp.clear(); int ones=0;
        for(int e:adj[v]){ if(st[e]==v) ones++; else tmp.push_back(H[e]); }
        if(ones>1) return false;
        sort(tmp.begin(),tmp.end());
        for(size_t i=1;i<tmp.size();i++) if(tmp[i]==tmp[i-1]) return false;
    }
    return true;
}
int main(){
    scanf("%d",&n);
    U.resize(n);V.resize(n);H.resize(n);adj.assign(n+1,{});
    for(int i=0;i<n;i++){scanf("%d %d %d",&U[i],&V[i],&H[i]);adj[U[i]].push_back(i);adj[V[i]].push_back(i);}
    vector<int> deg(n+1),st(n,0); vector<char> used(n,0);
    queue<int> q;
    for(int v=1;v<=n;v++){deg[v]=adj[v].size(); if(deg[v]==1) q.push(v);}
    while(!q.empty()){
        int v=q.front();q.pop();
        for(int e:adj[v]) if(!used[e]){
            used[e]=1; st[e]=v; int o=U[e]^V[e]^v;
            if(--deg[o]==1) q.push(o);
        }
        deg[v]=0;
    }
    int v0=-1;
    for(int v=1;v<=n;v++) if(deg[v]>=2){v0=v;break;}
    vector<int> a=st,b=st;
    int v=v0,prev=-1;
    do{
        int ne=-1;
        for(int e:adj[v]) if(!used[e]&&e!=prev){ne=e;break;}
        int o=U[ne]^V[ne]^v;
        a[ne]=v; b[ne]=o; prev=ne; v=o;
    }while(v!=v0);
    const vector<int>* ans=nullptr;
    if(valid(a)) ans=&a; else if(valid(b)) ans=&b;
    if(!ans){puts("impossible");return 0;}
    for(int i=0;i<n;i++) printf("%d\n",(*ans)[i]);
}
