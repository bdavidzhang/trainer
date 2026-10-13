#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; 
    static char buf[200005];
    scanf("%d",&n);
    vector<string> s(n);
    for(auto&x:s){ scanf("%s",buf); x=buf; }
    bool adj[26][26]={}; int indeg[26]={};
    for(int i=0;i+1<n;i++){
        const string&a=s[i],&b=s[i+1];
        size_t k=0; while(k<a.size()&&k<b.size()&&a[k]==b[k])k++;
        if(k==a.size()) continue;
        if(k==b.size()){ puts("impossible"); return 0; }
        int x=a[k]-'a',y=b[k]-'a';
        if(!adj[x][y]){adj[x][y]=true;indeg[y]++;}
    }
    string res; queue<int> q;
    for(int i=0;i<26;i++) if(!indeg[i]) q.push(i);
    while(!q.empty()){int u=q.front();q.pop();res+=char('a'+u);
        for(int v=0;v<26;v++) if(adj[u][v]&&--indeg[v]==0) q.push(v);}
    if(res.size()<26) puts("impossible"); else puts(res.c_str());
}
