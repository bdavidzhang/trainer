#include <bits/stdc++.h>
using namespace std;
// Choose N distinct points in [1,N]^2 forming an independent set in the conflict graph
// (a ~ b iff a+b is a card; a is unusable iff 2a is a card). Every vertex has degree <= N
// and corner vertices have much less, so a greedy in increasing-degree order succeeds for
// N>=2; randomized restarts and a final exhaustive search for tiny N are safety nets.
int N; vector<pair<int,int>> C; vector<vector<char>> isC;
vector<char> blocked; vector<int> chosen;
bool greedy(const vector<int>& order){
    fill(blocked.begin(),blocked.end(),0); chosen.clear();
    for(int p:order){
        if(blocked[p]) continue;
        int x=p/N+1,y=p%N+1;
        if(isC[2*x][2*y]) continue;
        chosen.push_back(p);
        if((int)chosen.size()==N) return true;
        for(auto&c:C){ int u=c.first-x,v=c.second-y; if(u>=1&&u<=N&&v>=1&&v<=N) blocked[(u-1)*N+v-1]=1; }
    }
    return false;
}
vector<int> bc;
bool dfs(const vector<int>& order,int start,int need){
    if(need==0) return true;
    int tot=order.size();
    for(int i=start;i<tot;i++){
        if(tot-i<need) return false;
        int p=order[i];
        if(bc[p]) continue;
        int x=p/N+1,y=p%N+1;
        if(isC[2*x][2*y]) continue;
        for(auto&c:C){ int u=c.first-x,v=c.second-y; if(u>=1&&u<=N&&v>=1&&v<=N) bc[(u-1)*N+v-1]++; }
        chosen.push_back(p);
        if(dfs(order,i+1,need-1)) return true;
        chosen.pop_back();
        for(auto&c:C){ int u=c.first-x,v=c.second-y; if(u>=1&&u<=N&&v>=1&&v<=N) bc[(u-1)*N+v-1]--; }
    }
    return false;
}
int main(){
    scanf("%d",&N);
    isC.assign(2*N+2,vector<char>(2*N+2,0));
    for(int i=0;i<N;i++){ int p,s; scanf("%d %d",&p,&s); if(!isC[p][s]){ isC[p][s]=1; C.push_back({p,s}); } }
    // degree via 2D prefix sums: #cards in [x+1,x+N]x[y+1,y+N]
    vector<vector<int>> pre(2*N+2,vector<int>(2*N+2,0));
    for(int i=1;i<=2*N;i++) for(int j=1;j<=2*N;j++) pre[i][j]=isC[i][j]+pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1];
    int tot=N*N;
    vector<int> deg(tot), order(tot);
    for(int p=0;p<tot;p++){ int x=p/N+1,y=p%N+1; deg[p]=pre[x+N][y+N]-pre[x][y+N]-pre[x+N][y]+pre[x][y]; order[p]=p; }
    { // counting sort by degree (stable)
        vector<int> cnt(N+2,0);
        for(int p=0;p<tot;p++) cnt[deg[p]+1]++;
        for(int i=1;i<=N+1;i++) cnt[i]+=cnt[i-1];
        for(int p=0;p<tot;p++) order[cnt[deg[p]]++]=p;
    }
    blocked.assign(tot,0);
    bool ok=greedy(order);
    auto t0=chrono::steady_clock::now();
    mt19937 rng(712367);
    vector<int> ord2(tot);
    while(!ok && chrono::duration<double>(chrono::steady_clock::now()-t0).count()<0.5){
        for(int p=0;p<tot;p++) ord2[p]=p;
        shuffle(ord2.begin(),ord2.end(),rng);
        ok=greedy(ord2);
    }
    if(!ok && N<=6){ bc.assign(tot,0); chosen.clear(); ok=dfs(order,0,N); }
    if(!ok){ puts("NO"); return 0; }
    puts("YES");
    for(int p:chosen) printf("%d %d\n",p/N+1,p%N+1);
}
