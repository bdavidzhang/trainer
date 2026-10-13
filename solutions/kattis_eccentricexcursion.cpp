#include <bits/stdc++.h>
using namespace std;
// Greedy lexicographic construction with an interval feasibility oracle.
// State: remaining forest F, start vertex w in F. Achievable numbers of roads used by a
// Hamiltonian ordering of F starting at w form the interval [mn(F,w), mx(F,w)].
int n,k;
vector<int> adj[505];
bool A[505][505];
bool alive[505];
int degF[505];
int g0[505],g1[505]; // g0: best in subtree with v having <=1 child edge; g1: best overall
int compBest[505],compId[505];
vector<int> order_; int par[505];
// iterative DP rooted at r over alive vertices; returns via g0/g1
void dp(int r){
    order_.clear();order_.push_back(r);par[r]=0;
    for(size_t i=0;i<order_.size();i++){int v=order_[i];for(int u:adj[v])if(alive[u]&&u!=par[v]){par[u]=v;order_.push_back(u);}}
    for(int i=(int)order_.size()-1;i>=0;i--){int v=order_[i];
        int base=0,b1=0,b2=0; // top two gains of (1+g0[c]-g1[c])
        for(int u:adj[v])if(alive[u]&&u!=par[v]){base+=g1[u];int gain=1+g0[u]-g1[u];if(gain>b1){b2=b1;b1=gain;}else if(gain>b2)b2=gain;}
        g0[v]=base+b1;g1[v]=base+b1+b2;}
}
int main(){
    scanf("%d %d",&n,&k);
    for(int i=0;i<n-1;i++){int a,b;scanf("%d %d",&a,&b);adj[a].push_back(b);adj[b].push_back(a);A[a][b]=A[b][a]=true;}
    for(int i=1;i<=n;i++){alive[i]=true;degF[i]=adj[i].size();}
    int need=n-1-k; // roads still to use
    int s=n,m=n-1,cur=0;
    vector<int> res;
    for(int step=0;step<n;step++){
        // component bests
        int total=0;
        vector<char> seen(n+1,0);
        for(int v=1;v<=n;v++)if(alive[v]&&!seen[v]){dp(v);for(int u:order_){seen[u]=1;compId[u]=v;}compBest[v]=g1[v];total+=g1[v];}
        // count of vertices with given degree for star test
        int pick=-1;
        for(int w=1;w<=n&&pick<0;w++){
            if(!alive[w])continue;
            int e=(cur&&A[cur][w])?1:0;
            int r=need-e;if(r<0)continue;
            dp(w);
            int mx=total-compBest[compId[w]]+g0[w];
            if(r>mx)continue;
            int mn;
            if(s==1)mn=0;
            else if(degF[w]==s-1)mn=1;
            else{
                mn=0;
                if(s-1>=2){
                    for(int c=1;c<=n;c++)if(alive[c]&&c!=w&&degF[c]-(A[c][w]?1:0)==s-2){mn=1;break;}
                }
            }
            if(r<mn)continue;
            pick=w;need=r;
        }
        if(pick<0){puts("-1");return 0;}
        res.push_back(pick);
        alive[pick]=false;s--;m-=degF[pick];
        for(int u:adj[pick])if(alive[u])degF[u]--;
        cur=pick;
    }
    for(int i=0;i<n;i++)printf("%d%c",res[i],i+1<n?' ':'\n');
}
