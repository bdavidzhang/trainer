#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,k;vector<ll> items[301];
vector<ll> dp,nd,pre;
int S,R,cntJ;int M;
// positions r + j*S, j in [0,cntJ)
static void solve(int lo,int hi,int ol,int oh){
    if(lo>hi)return;
    int mid=(lo+hi)/2;ll bv=-1;int bi=ol;
    int from=max(ol,mid-M),to=min(oh,mid);
    for(int i=from;i<=to;i++){ll v=dp[R+i*S]+pre[mid-i];if(v>bv){bv=v;bi=i;}}
    nd[R+mid*S]=bv;
    solve(lo,mid-1,ol,bi);solve(mid+1,hi,bi,oh);
}
int main(){
    scanf("%d %d",&n,&k);
    for(int i=0;i<n;i++){int s;ll v;scanf("%d %lld",&s,&v);items[s].push_back(v);}
    dp.assign(k+1,0);nd.assign(k+1,0);
    for(S=1;S<=300;S++){
        if(items[S].empty()||S>k)continue;
        sort(items[S].rbegin(),items[S].rend());
        M=min((int)items[S].size(),k/S);
        pre.assign(M+1,0);for(int i=0;i<M;i++)pre[i+1]=pre[i]+items[S][i];
        for(R=0;R<S&&R<=k;R++){cntJ=(k-R)/S+1;solve(0,cntJ-1,0,cntJ-1);}
        dp.swap(nd);
    }
    for(int i=1;i<=k;i++)printf("%lld%c",dp[i],i==k?'\n':' ');
}
