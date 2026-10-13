#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=4e18;
int main(){
    int n,q; ll m;
    if(scanf("%d %d %lld",&n,&q,&m)!=3) return 0;
    vector<ll> r(n+2),t(n+2);
    for(int i=1;i<=n;i++)scanf("%lld",&r[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&t[i]);
    // par[i]: lowest j with r_j >= r_i - m ; nxt[i]: largest k with r_k <= r_i + m
    vector<int> par(n+2),nxt(n+2);
    {int j=1;for(int i=1;i<=n;i++){while(r[j]<r[i]-m)j++;par[i]=j;}}
    {int k=1;for(int i=1;i<=n;i++){while(k<n&&r[k+1]<=r[i]+m)k++;nxt[i]=k;}}
    // sparse table for min t
    int LG=1;while((1<<LG)<=n)LG++;
    vector<vector<ll>> sp(LG,vector<ll>(n+2,INF));
    for(int i=1;i<=n;i++)sp[0][i]=t[i];
    for(int j=1;j<LG;j++)for(int i=1;i+(1<<j)-1<=n;i++)sp[j][i]=min(sp[j-1][i],sp[j-1][i+(1<<(j-1))]);
    vector<int> lg(n+2,0);for(int i=2;i<=n+1;i++)lg[i]=lg[i/2]+1;
    auto rmq=[&](int l,int rr)->ll{if(l>rr)return INF;int j=lg[rr-l+1];return min(sp[j][l],sp[j][rr-(1<<j)+1]);};
    vector<ll> pre(n+2,INF);
    for(int i=1;i<=n;i++)pre[i]=min(pre[i-1],t[i]);
    // forward tree depth
    vector<int> fd(n+2,0);
    for(int i=n;i>=1;i--) fd[i]= nxt[i]==i?0:fd[nxt[i]]+1;
    vector<vector<int>> up(LG,vector<int>(n+2));
    vector<vector<ll>> mn(LG,vector<ll>(n+2,INF));
    for(int i=1;i<=n;i++){
        up[0][i]=nxt[i];
        if(nxt[i]!=i){ll w=rmq(i+1,nxt[i]); mn[0][i]=w-fd[i];}
    }
    for(int j=1;j<LG;j++)for(int i=1;i<=n;i++){
        up[j][i]=up[j-1][up[j-1][i]];
        mn[j][i]=min(mn[j-1][i],mn[j-1][up[j-1][i]]);
    }
    while(q--){
        int x,y;scanf("%d %d",&x,&y);
        if(y>=par[x]){puts("1");continue;}
        ll ans=1+t[y];
        if(y>1) ans=min(ans,2+pre[y-1]);
        // free path
        {
            int v=y; ll steps=0;
            for(int j=LG-1;j>=0;j--) if(up[j][v]<x && up[j][v]!=v){steps+=1LL<<j;v=up[j][v];}
            if(nxt[v]>=x) ans=min(ans,steps+1);
        }
        // quarantine at k in (y, R), R=par[x]
        {
            int R=par[x];
            int v=y; ll acc=INF;
            for(int j=LG-1;j>=0;j--) if(up[j][v]<R && up[j][v]!=v){acc=min(acc,mn[j][v]);v=up[j][v];}
            if(acc<INF/2) ans=min(ans,1+acc+fd[y]+1);
            if(nxt[v]!=v){
                // nxt[v]>=R; partial block (v,R-1]
                ll w=rmq(v+1,R-1);
                if(w<INF/2) ans=min(ans,1+w+(fd[y]-fd[v]+1));
            }
        }
        printf("%lld\n",ans);
    }
}
