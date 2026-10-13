#include <bits/stdc++.h>
using namespace std;
int n; char s[5005]; vector<int> adj[5005];
int st[5005],sp; long long ans;
int typ[5005]; bool op[5005];
void dfs(int u,int p){
    // u already pushed/processed
    if(sp==0) ans++;
    for(int v:adj[u]) if(v!=p){
        if(op[v]){ st[sp++]=typ[v]; dfs(v,u); sp--; }
        else if(sp>0 && st[sp-1]==typ[v]){ sp--; dfs(v,u); st[sp++]=typ[v]; }
    }
}
int main(){
    scanf("%d %s",&n,s+1);
    for(int i=1;i<=n;i++){
        char c=s[i];
        op[i]=(c=='('||c=='['||c=='{');
        typ[i]=(c=='('||c==')')?0:(c=='['||c==']')?1:2;
    }
    for(int i=1;i<n;i++){int u,v;scanf("%d %d",&u,&v);adj[u].push_back(v);adj[v].push_back(u);}
    for(int i=1;i<=n;i++) if(op[i]){ sp=0; st[sp++]=typ[i]; dfs(i,0); }
    printf("%lld\n",ans);
}
