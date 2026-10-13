#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,q;
    if(!(cin>>n>>q))return 0;
    map<string,int> id;
    vector<vector<pair<int,double>>> g;
    auto get=[&](const string&s){auto it=id.find(s);if(it!=id.end())return it->second;int k=id.size();id[s]=k;g.emplace_back();return k;};
    for(int i=0;i<n;i++){
        string one,a,eq,b;double v;
        cin>>one>>a>>eq>>v>>b;
        int x=get(a),y=get(b);
        // 1 a = v b : log(unit a) = log v + log(unit b)
        g[x].push_back({y,log(v)});
        g[y].push_back({x,-log(v)});
    }
    int V=id.size();
    vector<int> comp(V,-1);vector<double> lg(V,0);
    for(int s=0;s<V;s++)if(comp[s]<0){
        comp[s]=s;vector<int> st{s};
        while(!st.empty()){int u=st.back();st.pop_back();
            for(auto&e:g[u])if(comp[e.first]<0){comp[e.first]=s;lg[e.first]=lg[u]-e.second;st.push_back(e.first);}
        }
    }
    // lg[u] = log(size of unit u) relative to root
    while(q--){
        double v;string a,to,b;cin>>v>>a>>to>>b;
        int x=id[a],y=id[b];
        if(comp[x]!=comp[y]){puts("impossible");continue;}
        double r=exp(log(v)+lg[x]-lg[y]);
        printf("%.12e\n",r);
    }
}
