#include <bits/stdc++.h>
using namespace std;
int n,k;
vector<string> ord_;
vector<char> tk;
vector<vector<int>> g;
vector<int> mt; vector<char> vis;
bool tryk(int u){
    for(int v:g[u]) if(!vis[v]){
        vis[v]=1;
        if(mt[v]<0||tryk(mt[v])){mt[v]=u;return true;}
    }
    return false;
}
int main(){
    cin>>n>>k;
    ord_.resize(n); for(auto&s:ord_)cin>>s;
    tk.resize(k); for(auto&c:tk)cin>>c;
    char t,m; cin>>t>>m;
    // does a world without violators exist? match tickets to non-violating orders
    g.assign(k,{});
    bool anyBad=false; bool badLetter[26]={};
    for(int j=0;j<n;j++) if(ord_[j][1]==t&&ord_[j][0]!=m){anyBad=true;badLetter[ord_[j][0]-'A']=true;}
    for(int i=0;i<k;i++)for(int j=0;j<n;j++){
        if(ord_[j][1]==t&&ord_[j][0]!=m)continue;
        if(ord_[j][0]==tk[i]||ord_[j][1]==tk[i]) g[i].push_back(j);
    }
    mt.assign(n,-1); int sz=0;
    for(int i=0;i<k;i++){vis.assign(n,0); if(tryk(i))sz++;}
    if(sz<k){puts("false");return 0;}
    vector<int> res;
    for(int i=0;i<k;i++){
        if(isdigit((unsigned char)tk[i])){ if(tk[i]==t&&anyBad)res.push_back(i+1); }
        else if(tk[i]!=m&&badLetter[tk[i]-'A'])res.push_back(i+1);
    }
    if(res.empty()){puts("true");return 0;}
    printf("%d\n",(int)res.size());
    for(size_t i=0;i<res.size();i++)printf("%d%c",res[i],i+1==res.size()?'\n':' ');
}
