#include <bits/stdc++.h>
using namespace std;
int n,k,m;
vector<int> ch[250001];
int par[250001],tin[250001],tout[250001],dep[250001];
int bit[250002];
void upd(int i,int v){ for(;i<=n+1;i+=i&-i) bit[i]+=v; }
int qry(int i){ int s=0; for(;i>0;i-=i&-i) s+=bit[i]; return s; }
int main(){
    scanf("%d %d %d",&n,&k,&m);
    for(int i=0;i<k;i++){ int u,v; scanf("%d %d",&u,&v); ch[u].push_back(v); par[v]=u; }
    int timer=0;
    for(int r=1;r<=n;r++) if(!par[r]){
        vector<pair<int,int>> st; st.push_back({r,0}); tin[r]=++timer; dep[r]=0;
        while(!st.empty()){
            int u=st.back().first; int &i=st.back().second;
            if(i<(int)ch[u].size()){ int v=ch[u][i++]; dep[v]=dep[u]+1; tin[v]=++timer; st.push_back({v,0}); }
            else { tout[u]=timer; st.pop_back(); }
        }
    }
    vector<pair<int,int>> pl(m);
    for(auto&p:pl) scanf("%d %d",&p.first,&p.second);
    sort(pl.begin(),pl.end(),[&](const pair<int,int>&a,const pair<int,int>&b){ return dep[a.first]>dep[b.first]; });
    int ans=0;
    for(auto&p:pl){
        int s=p.first,t=p.second;
        int cnt=qry(tin[t]) - (par[s]? qry(tin[par[s]]):0);
        if(cnt==0){ ans++; upd(tin[s],1); upd(tout[s]+1,-1); }
    }
    printf("%d\n",ans);
}
