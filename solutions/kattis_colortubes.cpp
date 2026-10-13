#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> tb; // bottom..top
vector<pair<int,int>> moves;
void mv(int u,int v){
    assert(u!=v && !tb[u].empty() && tb[v].size()<3);
    tb[v].push_back(tb[u].back()); tb[u].pop_back();
    moves.push_back({u,v});
}
// make every tube in cand either full or empty (total holes among partial ones is 3)
void consolidate(const vector<int>& cand){
    while(true){
        int src=-1;
        for(int t:cand){ int s=tb[t].size(); if(s>0&&s<3&&(src<0||s<(int)tb[src].size())) src=t; }
        if(src<0) break;
        int dst=-1;
        for(int t:cand){ int s=tb[t].size(); if(t!=src&&s>0&&s<3){dst=t;break;} }
        assert(dst>=0);
        mv(src,dst);
    }
}
int main(){
    scanf("%d",&n);
    tb.assign(n+1,{});
    for(int i=0;i<=n;i++){ for(int k=0;k<3;k++){int c;scanf("%d",&c); if(c) tb[i].push_back(c);} }
    vector<int> all(n+1); iota(all.begin(),all.end(),0);
    consolidate(all);
    int E=-1; for(int i=0;i<=n;i++) if(tb[i].empty()) E=i;
    assert(E>=0);
    auto solvedTube=[&](int t){return tb[t].size()==3&&tb[t][0]==tb[t][1]&&tb[t][1]==tb[t][2];};
    while(true){
        // depth sums per colour over unsolved tubes
        vector<int> sum(n+1,0), mids(n+1,0); vector<char> act(n+1,0);
        bool any=false;
        for(int t=0;t<=n;t++){ if(t==E||solvedTube(t))continue; any=true;
            for(int k=0;k<3;k++){ int c=tb[t][k]; act[c]=1; sum[c]+=2-k; if(k==1) mids[c]++; } }
        if(!any) break;
        int best=-1;
        for(int c=1;c<=n;c++){ if(!act[c]||mids[c]==3)continue; if(best<0||sum[c]<sum[best]) best=c; }
        assert(best>=0 && sum[best]<=3);
        int c=best;
        vector<pair<int,int>> loc; // (depth, tube)
        vector<int> inv;
        for(int t=0;t<=n;t++){ if(t==E||solvedTube(t))continue; bool has=false;
            for(int k=0;k<3;k++) if(tb[t][k]==c){loc.push_back({2-k,t});has=true;}
            if(has) inv.push_back(t); }
        sort(loc.begin(),loc.end());
        for(auto&pr:loc){ int T=pr.second;
            while(tb[T].back()!=c){
                int dst=-1;
                for(int t:inv) if(t!=T&&tb[t].size()<3){dst=t;break;}
                assert(dst>=0);
                mv(T,dst);
            }
            mv(T,E);
        }
        consolidate(inv);
        int nE=-1; for(int t:inv) if(tb[t].empty()) nE=t;
        assert(nE>=0); E=nE;
    }
    printf("%d\n",(int)moves.size());
    for(auto&m:moves) printf("%d %d\n",m.first+1,m.second+1);
}
