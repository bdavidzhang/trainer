#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<vector<int>> g(n+1);
    for(int i=0;i<n-1;i++){int u,v;scanf("%d %d",&u,&v);g[u].push_back(v);g[v].push_back(u);}
    for(int v=1;v<=n;v++) if((int)g[v].size()==n-1){ puts("NO"); return 0; }
    // centroid
    vector<int> par(n+1,0),ord,sz(n+1,1);
    ord.reserve(n);
    { vector<int> st={1}; par[1]=0;
      while(!st.empty()){int v=st.back();st.pop_back();ord.push_back(v);for(int w:g[v]) if(w!=par[v]){par[w]=v;st.push_back(w);} } }
    for(int i=n-1;i>0;i--) sz[par[ord[i]]]+=sz[ord[i]];
    int c=1;
    for(int v=1;v<=n;v++){
        int mx=n-sz[v];
        for(int w:g[v]) if(w!=par[v]) mx=max(mx,sz[w]);
        if(mx<=n/2){c=v;break;}
    }
    // groups: child subtrees of c
    int k=g[c].size();
    vector<vector<int>> grp(k);
    for(int i=0;i<k;i++){
        int w=g[c][i];
        vector<int> st={w}; vector<int>& L=grp[i];
        vector<pair<int,int>> s2={{w,c}};
        while(!s2.empty()){auto [v,p]=s2.back();s2.pop_back();L.push_back(v);for(int u:g[v]) if(u!=p) s2.push_back({u,v});}
    }
    int W=0;
    for(int i=0;i<k;i++) if(grp[i].size()>grp[W].size()) W=i;
    // grp[W][0] is w itself; take y = last element (!= w since size>=2)
    vector<int> res;
    int y=grp[W].back(); grp[W].pop_back();
    res.push_back(y); res.push_back(c);
    priority_queue<pair<int,int>> pq;
    for(int i=0;i<k;i++) if(!grp[i].empty()) pq.push({(int)grp[i].size(),i});
    int last=W;
    while(!pq.empty()){
        auto t=pq.top(); pq.pop();
        if(t.second==last){
            if(pq.empty()){ // should not happen
                fprintf(stderr,"stuck\n"); 
                res.push_back(grp[t.second].back()); grp[t.second].pop_back();
                if(--t.first) pq.push(t);
                continue;
            }
            auto u=pq.top(); pq.pop(); pq.push(t); t=u;
        }
        res.push_back(grp[t.second].back()); grp[t.second].pop_back();
        last=t.second;
        if(--t.first) pq.push(t);
    }
    puts("YES");
    for(int i=0;i<n;i++) printf("%d%c",res[i],i+1<n?' ':'\n');
}
