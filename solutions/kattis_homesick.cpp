#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m;scanf("%d %d",&n,&m);
    vector<int> eu(m),ev(m);
    vector<vector<int>> adj(n+1); // arc ids leaving vertex; arc 2e: u->v, 2e+1: v->u
    for(int e=0;e<m;e++){
        scanf("%d %d",&eu[e],&ev[e]);
        adj[eu[e]].push_back(2*e);
        adj[ev[e]].push_back(2*e+1);
    }
    auto head=[&](int a){return (a&1)?eu[a>>1]:ev[a>>1];};
    vector<int> par(2*m,-2);
    vector<int> cnt(n+1,0);
    queue<int> q;
    for(int a:adj[1]){par[a]=-1;q.push(a);}
    int fin=-1;
    while(!q.empty()){
        int a=q.front();q.pop();
        int v=head(a);
        if(v==1){fin=a;break;}
        if(cnt[v]>=2)continue;
        cnt[v]++;
        for(int b:adj[v]){
            if(b==(a^1))continue;
            if(par[b]!=-2)continue;
            par[b]=a;q.push(b);
        }
    }
    if(fin<0){puts("impossible");return 0;}
    vector<int> path;
    for(int a=fin;a!=-1;a=par[a])path.push_back(head(a));
    path.push_back(1);
    reverse(path.begin(),path.end());
    printf("%d\n",(int)path.size());
    for(size_t i=0;i<path.size();i++)printf("%d%c",path[i],i+1==path.size()?'\n':' ');
}
