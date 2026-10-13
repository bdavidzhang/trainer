#include <bits/stdc++.h>
using namespace std;
// Color coding: map serial numbers to 7 colors (balanced random partition), then
// dp[mask][v] = min cost to stand at v holding colors mask; one Dijkstra per mask.
const int INF=INT_MAX/2;
int n,m,k;
vector<int> st,to,wt;
int main(){
    auto T0=chrono::steady_clock::now();
    scanf("%d %d %d",&n,&m,&k);
    vector<array<int,3>> es(m);
    st.assign(n+2,0);
    for(auto&e:es){scanf("%d %d %d",&e[0],&e[1],&e[2]);e[0]--;e[1]--;st[e[0]+1]++;st[e[1]+1]++;}
    for(int i=1;i<=n+1;i++)st[i]+=st[i-1];
    to.resize(2*m);wt.resize(2*m);
    {vector<int>pos(st.begin(),st.end());for(auto&e:es){to[pos[e[0]]]=e[1];wt[pos[e[0]]++]=e[2];to[pos[e[1]]]=e[0];wt[pos[e[1]]++]=e[2];}}
    typedef pair<int,int> pii;
    vector<pii> heapbuf;
    int best=INF;
    auto dijkstra=[&](vector<int>&d){
        priority_queue<pii,vector<pii>,greater<pii>> pq;
        for(int v=0;v<n;v++)if(d[v]<best)pq.push({d[v],v});
        while(!pq.empty()){
            auto [dv,v]=pq.top();pq.pop();
            if(dv>d[v])continue;
            for(int j=st[v];j<st[v+1];j++){int nd=dv+wt[j];if(nd<d[to[j]]&&nd<best){d[to[j]]=nd;pq.push({nd,to[j]});}}
        }
    };
    vector<int> d0(n,INF);d0[0]=0;dijkstra(d0);
    vector<pii> balls;
    for(int i=0;i<k;i++){int c,s;scanf("%d %d",&c,&s);c--;if(d0[c]<INF)balls.push_back({c,s});}
    sort(balls.begin(),balls.end());balls.erase(unique(balls.begin(),balls.end()),balls.end());
    vector<int> ser;for(auto&b:balls)ser.push_back(b.second);
    sort(ser.begin(),ser.end());ser.erase(unique(ser.begin(),ser.end()),ser.end());
    int S=ser.size();
    if(S<7){puts("-1");return 0;}
    for(auto&b:balls)b.second=lower_bound(ser.begin(),ser.end(),b.second)-ser.begin();
    const int Q=7;
    vector<vector<int>> dp(1<<Q,vector<int>(n));
    vector<int> perm(S),col(S);iota(perm.begin(),perm.end(),0);
    mt19937 rng(712367);
    // order masks by popcount is implied by numeric order (submasks are smaller)
    int trial=0;
    while(true){
        shuffle(perm.begin(),perm.end(),rng);
        for(int i=0;i<S;i++)col[perm[i]]=i%Q;
        // per color list of cities
        vector<vector<int>> at(Q);
        for(auto&b:balls)at[col[b.second]].push_back(b.first);
        dp[0]=d0;
        for(int mask=1;mask<(1<<Q);mask++){
            auto&d=dp[mask];
            fill(d.begin(),d.end(),INF);
            for(int c=0;c<Q;c++)if(mask>>c&1){auto&pr=dp[mask^(1<<c)];for(int v:at[c])if(pr[v]<d[v])d[v]=pr[v];}
            if(mask==(1<<Q)-1){for(int v=0;v<n;v++)best=min(best,d[v]);}
            else dijkstra(d);
        }
        trial++;
        if(S==7)break;
        if((trial&3)==0){
            double el=chrono::duration<double>(chrono::steady_clock::now()-T0).count();
            if(el>7.5)break;
        }
    }
    printf("%d\n",best>=INF?-1:best);
}
