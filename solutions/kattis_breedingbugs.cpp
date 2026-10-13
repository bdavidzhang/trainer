#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj; vector<int> mt; vector<char> vis;
bool tryk(int u){
    for(int v:adj[u]) if(!vis[v]){ vis[v]=1; if(mt[v]<0||tryk(mt[v])){mt[v]=u;return true;} }
    return false;
}
int main(){
    int n; scanf("%d",&n);
    vector<int> od,ev; bool one=false;
    for(int i=0;i<n;i++){ int p; scanf("%d",&p);
        if(p==1){ if(one) continue; one=true; }
        if(p&1) od.push_back(p); else ev.push_back(p); }
    const int M=20000000;
    vector<bool> comp(M+1,false);
    for(long long i=3;i*i<=M;i+=2) if(!comp[i]) for(long long j=i*i;j<=M;j+=2*i) comp[j]=true;
    adj.assign(od.size(),{});
    for(size_t i=0;i<od.size();i++) for(size_t j=0;j<ev.size();j++){
        int s=od[i]+ev[j]; // odd, >=3
        if(!comp[s]) adj[i].push_back(j);
    }
    mt.assign(ev.size(),-1); int match=0;
    for(size_t i=0;i<od.size();i++){ vis.assign(ev.size(),0); if(tryk(i)) match++; }
    printf("%d\n",(int)(od.size()+ev.size())-match);
}
