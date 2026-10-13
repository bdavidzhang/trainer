#include <bits/stdc++.h>
using namespace std;
// 1) Kleitman-Wang: lay off the out-degree of a vertex onto the vertices with the largest
//    remaining in-degree (ties: larger remaining out-degree), never onto itself.
// 2) Make it weakly connected with arc swaps (u1->v1, u2->v2) => (u1->v2, u2->v1) between two
//    components, always using a non-tree (cycle) arc on at least one side.
static vector<int> dsu;
static int fnd(int x){ while(dsu[x]!=x){ dsu[x]=dsu[dsu[x]]; x=dsu[x]; } return x; }
bool solveCase(int n,vector<int> a,vector<int> b,vector<pair<int,int>>&arcs){
    arcs.clear();
    long long sa=0,sb=0; for(int i=0;i<n;i++){ sa+=a[i]; sb+=b[i]; }
    if(sa!=sb) return false;
    if(n==1) return sa==0;
    for(int i=0;i<n;i++) if(a[i]+b[i]==0||a[i]>n-1||b[i]>n-1) return false;
    if(sa<n-1) return false;
    typedef array<int,3> K;                       // (remaining in, remaining out, id)
    set<K> st;
    for(int i=0;i<n;i++) if(b[i]>0) st.insert({b[i],a[i],i});
    arcs.reserve(sa);
    vector<K> taken;
    for(int v=0;v<n;v++){
        if(a[v]==0) continue;
        int need=a[v];
        if(b[v]>0){ st.erase({b[v],a[v],v}); }
        a[v]=0;
        taken.clear();
        auto it=st.end();
        while((int)taken.size()<need){
            if(it==st.begin()) return false;
            --it; taken.push_back(*it);
        }
        for(auto &k:taken) st.erase(k);
        for(auto &k:taken){
            arcs.push_back({v,k[2]});
            b[k[2]]--;
            if(b[k[2]]>0) st.insert({b[k[2]],k[1],k[2]});
        }
        if(b[v]>0) st.insert({b[v],0,v});
    }
    if(!st.empty()) return false;
    int m=arcs.size();
    dsu.resize(n); iota(dsu.begin(),dsu.end(),0);
    vector<char> isTree(m,0);
    for(int e=0;e<m;e++){ int x=fnd(arcs[e].first),y=fnd(arcs[e].second); if(x!=y){ dsu[x]=y; isTree[e]=1; } }
    vector<vector<int>> spare(n); vector<int> anyArc(n,-1);
    for(int e=0;e<m;e++){ int r=fnd(arcs[e].first); if(isTree[e]) anyArc[r]=e; else spare[r].push_back(e); }
    vector<int> cyc,tree;
    for(int i=0;i<n;i++) if(fnd(i)==i){ if(!spare[i].empty()) cyc.push_back(i); else tree.push_back(i); }
    if(cyc.size()+tree.size()==1) return true;
    if(cyc.empty()) return false;                 // cannot happen when m>=n-1 and several components
    vector<int> pool=spare[cyc[0]];
    for(size_t j=1;j<cyc.size();j++){
        auto &sp=spare[cyc[j]];
        int e1=pool.back(); pool.pop_back();
        int e2=sp.back(); sp.pop_back();
        swap(arcs[e1].second,arcs[e2].second);   // e1 joins the spanning trees, e2 closes a cycle
        pool.push_back(e2);
        for(int e:sp) pool.push_back(e);
    }
    for(int r:tree){
        if(pool.empty()) return false;            // cannot happen by the counting argument
        int e1=pool.back(); pool.pop_back();
        int e2=anyArc[r];
        swap(arcs[e1].second,arcs[e2].second);
    }
    return true;
}
int main(){
    int n; if(scanf("%d",&n)!=1) return 0;
    vector<int> a(n),b(n);
    for(auto &x:a) scanf("%d",&x);
    for(auto &x:b) scanf("%d",&x);
    vector<pair<int,int>> arcs;
    if(!solveCase(n,a,b,arcs)){ puts("impossible"); return 0; }
    string out=to_string(n)+" "+to_string(arcs.size())+"\n";
    out.reserve(arcs.size()*14+32);
    for(auto &e:arcs){ out+=to_string(e.first+1); out+=' '; out+=to_string(e.second+1); out+='\n'; }
    fputs(out.c_str(),stdout);
    return 0;
}
