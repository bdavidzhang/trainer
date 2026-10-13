#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m,k; scanf("%d %d %d",&n,&m,&k);
    vector<vector<int>> g(n+1);
    for(int i=0;i<m;i++){int x,y;scanf("%d %d",&x,&y);g[x].push_back(y);g[y].push_back(x);}
    vector<int> deg(n+1),ord; vector<char> rem(n+1,0);
    ord.reserve(n);
    for(int i=1;i<=n;i++){deg[i]=g[i].size(); if(deg[i]<=k){rem[i]=1;ord.push_back(i);}}
    for(size_t h=0;h<ord.size();h++){
        int v=ord[h];
        for(int u:g[v]) if(!rem[u]){ if(--deg[u]<=k){rem[u]=1;ord.push_back(u);} }
    }
    vector<int> col(n+1,0),mark(n+3,0);
    for(int h=(int)ord.size()-1;h>=0;h--){
        int v=ord[h];
        for(int u:g[v]) if(col[u]) mark[col[u]]=v;
        int c=1; while(mark[c]==v) c++;
        col[v]=c;
    }
    for(int i=1;i<=n;i++) printf("%d%c",col[i]?col[i]:1,i==n?'\n':' ');
}
