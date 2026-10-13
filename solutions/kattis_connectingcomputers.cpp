#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m,k;
    cin>>n>>m>>k;
    unordered_map<string,int> id;
    for(int i=0;i<k;i++){string s;cin>>s;id[s]=i;}
    vector<vector<pair<int,int>>> adj(n+1); // (to, edge idx)
    vector<int> et(m);
    for(int i=0;i<m;i++){int x,y;string s;cin>>x>>y>>s;et[i]=id[s];adj[x].push_back({y,i});adj[y].push_back({x,i});}
    vector<int> par(n+1,0),pe(n+1,-1),dep(n+1,-1),it(n+1,0);
    vector<char> covered(m,0);
    unsigned forbid=0;
    vector<unsigned> conf(k,0);
    vector<int> st;st.push_back(1);dep[1]=0;
    int cnt[24];
    while(!st.empty()){
        int u=st.back();
        if(it[u]<(int)adj[u].size()){
            auto [v,e]=adj[u][it[u]++];
            if(e==pe[u])continue;
            if(dep[v]<0){dep[v]=dep[u]+1;par[v]=u;pe[v]=e;st.push_back(v);}
            else if(dep[v]<dep[u]){
                // back edge u->v ancestor: cycle
                memset(cnt,0,sizeof cnt);
                cnt[et[e]]++;covered[e]=1;
                int x=u;
                while(x!=v){cnt[et[pe[x]]]++;covered[pe[x]]=1;x=par[x];}
                unsigned single=0;
                for(int t=0;t<k;t++){if(cnt[t]>=2)forbid|=1u<<t;else if(cnt[t]==1)single|=1u<<t;}
                for(int t=0;t<k;t++)if(single>>t&1)conf[t]|=single&~(1u<<t);
            }
        } else st.pop_back();
    }
    for(int i=0;i<m;i++)if(!covered[i])forbid|=1u<<et[i];
    // count independent sets R avoiding forbid
    vector<char> ok(1u<<k,0);
    ok[0]=1;
    long long total=1;int best=0;
    for(unsigned mask=1;mask<(1u<<k);mask++){
        int b=__builtin_ctz(mask);
        unsigned rest=mask&(mask-1);
        if(ok[rest]&&!(forbid>>b&1)&&!(conf[b]&rest)){
            ok[mask]=1;total++;
            int pc=__builtin_popcount(mask);if(pc>best)best=pc;
        }
    }
    cout<<k-best<<"\n"<<total<<"\n";
}
