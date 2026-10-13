#include <bits/stdc++.h>
using namespace std;
int n; vector<vector<int>> g; vector<int> mt, vis; int stamp=0;
bool tryk(int u){
    for(int v:g[u]) if(vis[v]!=stamp){vis[v]=stamp; if(mt[v]<0||tryk(mt[v])){mt[v]=u;return true;}}
    return false;
}
int main(){
    cin>>n; vector<string> w(n); for(auto&s:w)cin>>s;
    g.assign(n,{});
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
        int d=0; for(size_t k=0;k<w[i].size()&&d<3;k++) if(w[i][k]!=w[j][k]) d++;
        if(d==2){g[i].push_back(j);g[j].push_back(i);}
    }
    vector<int> col(n,-1);
    for(int s=0;s<n;s++) if(col[s]<0){col[s]=0; queue<int> q;q.push(s);
        while(!q.empty()){int u=q.front();q.pop();for(int v:g[u])if(col[v]<0){col[v]=col[u]^1;q.push(v);}}}
    mt.assign(n,-1); vis.assign(n,0); int m=0;
    for(int i=0;i<n;i++) if(col[i]==0){stamp++; if(tryk(i)) m++;}
    printf("%d\n", n-m);
}
