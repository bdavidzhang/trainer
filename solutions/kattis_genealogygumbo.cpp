#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);unordered_map<string,int> id;vector<vector<int>> g;
 auto gid=[&](const string&s){auto it=id.find(s);if(it!=id.end())return it->second;int k=id.size();id[s]=k;g.emplace_back();return k;};
 char A[64],w1[16],w2[16],B[64];
 for(int i=0;i<n;i++){scanf("%s %s %s %s",A,w1,w2,B);string a(A);if(!a.empty()&&a.back()==',')a.pop_back();int x=gid(a),y=gid(string(B));g[y].push_back(x);}
 int V=g.size();vector<char> vis(V,0);
 auto dfs=[&](int s){vector<int> st{s};vis[s]=1;while(!st.empty()){int u=st.back();st.pop_back();for(int w:g[u])if(!vis[w]){vis[w]=1;st.push_back(w);}}};
 int cand=-1;for(int v=0;v<V;v++)if(!vis[v]){dfs(v);cand=v;}
 fill(vis.begin(),vis.end(),0);dfs(cand);
 for(int v=0;v<V;v++)if(!vis[v]){puts("impossible");return 0;}
 puts("possible");}
