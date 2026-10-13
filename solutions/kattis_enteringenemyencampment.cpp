#include <bits/stdc++.h>
using namespace std;
// D = P1-P2 = 1/2 * sum_v s_v*(2*before(v)-deg(v)); gain depends only on claimed set.
int main(){int n,m;scanf("%d %d",&n,&m);vector<int> adj(n,0),deg(n,0);
for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);a--;b--;adj[a]|=1<<b;adj[b]|=1<<a;deg[a]++;deg[b]++;}
int F=(1<<n)-1;vector<short> dp(1<<n,0); // value for player to move (mover minus other), doubled
for(int S=F-1;S>=0;S--){int best=INT_MIN;
for(int v=0;v<n;v++)if(!(S>>v&1)){int g=2*__builtin_popcount(adj[v]&S)-deg[v];int val=g-dp[S|1<<v];if(val>best)best=val;}
dp[S]=best;}
int r=dp[0];puts(r>0?"player 1":r<0?"player 2":"tie");}
