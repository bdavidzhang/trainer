#include <bits/stdc++.h>
using namespace std;
int main(){
    char L; int n; cin>>L>>n; int k=L-'a'+1;
    vector<string> w(n); for(auto&s:w)cin>>s;
    bool adj[26][26]={}; int indeg[26]={}; bool bad=false;
    for(int i=0;i+1<n;i++){
        const string&a=w[i],&b=w[i+1]; size_t j=0;
        while(j<a.size()&&j<b.size()&&a[j]==b[j])j++;
        if(j==a.size())continue;
        if(j==b.size()){bad=true;break;}
        int x=a[j]-'a',y=b[j]-'a';
        if(!adj[x][y]){adj[x][y]=true;indeg[y]++;}
    }
    if(bad){puts("IMPOSSIBLE");return 0;}
    vector<int> q; for(int i=0;i<k;i++)if(!indeg[i])q.push_back(i);
    bool amb=false; string res; size_t h=0;
    while(h<q.size()){
        if(q.size()-h>1)amb=true;
        int u=q[h++]; res+=char('a'+u);
        for(int v=0;v<k;v++)if(adj[u][v]&&--indeg[v]==0)q.push_back(v);
    }
    if((int)res.size()<k)puts("IMPOSSIBLE");
    else if(amb)puts("AMBIGUOUS");
    else puts(res.c_str());
}
