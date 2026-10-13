#include <bits/stdc++.h>
using namespace std;
int main(){
    int M,N;
    if(scanf("%d %d",&M,&N)!=2) return 0;
    unordered_map<string,int> id;
    vector<vector<pair<int,int>>> g;
    char s1[20],s2[20];
    auto get=[&](const char*s){
        auto it=id.find(s);
        if(it!=id.end()) return it->second;
        int k=id.size(); id[s]=k; g.emplace_back(); return k;
    };
    for(int i=0;i<M+N;i++){
        scanf("%s %s",s1,s2);
        int a=get(s1),b=get(s2);
        g[a].push_back({b,i>=M});
    }
    int n=g.size();
    vector<int> idx(n,-1),low(n,0),comp(n,-1),it(n,0),st,cs;
    int timer=0,nc=0;
    for(int r=0;r<n;r++) if(idx[r]<0){
        cs.push_back(r); idx[r]=low[r]=timer++; st.push_back(r);
        while(!cs.empty()){
            int u=cs.back();
            if(it[u]<(int)g[u].size()){
                int v=g[u][it[u]++].first;
                if(idx[v]<0){ idx[v]=low[v]=timer++; st.push_back(v); cs.push_back(v);}
                else if(comp[v]<0) low[u]=min(low[u],idx[v]);
            } else {
                if(low[u]==idx[u]){
                    while(true){int w=st.back();st.pop_back();comp[w]=nc;if(w==u)break;}
                    nc++;
                }
                cs.pop_back();
                if(!cs.empty()) low[cs.back()]=min(low[cs.back()],low[u]);
            }
        }
    }
    vector<vector<int>> members(nc);
    for(int i=0;i<n;i++) members[comp[i]].push_back(i);
    vector<int> lvl(nc,0);
    int best=0;
    for(int c=0;c<nc;c++){
        for(int u:members[c]) for(auto&e:g[u]){
            int d=comp[e.first];
            if(d!=c) lvl[c]=max(lvl[c],lvl[d]+e.second);
        }
        best=max(best,lvl[c]);
    }
    printf("%d %d\n",best+1,nc);
}
