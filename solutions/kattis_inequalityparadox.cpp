#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n; bool g[26][26]={}; int indeg[26]={};
    for(int i=0;i<n;i++){char a,x,b;cin>>a>>x>>b;int u=a-'a',v=b-'a';if(x=='>')swap(u,v); if(!g[u][v]){g[u][v]=true;indeg[v]++;}}
    vector<int> q; for(int i=0;i<26;i++) if(!indeg[i]) q.push_back(i);
    for(size_t h=0;h<q.size();h++){int u=q[h];for(int v=0;v<26;v++) if(g[u][v]&&--indeg[v]==0) q.push_back(v);}
    puts(q.size()==26?":)":":(");
}
