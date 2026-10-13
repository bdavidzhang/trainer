#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef __int128 LL;
static const ll INF=LLONG_MAX/4;
int n; vector<int> rk; vector<ll> dp; vector<int> ord,tmp;
vector<ll> hs,hi; // hull slopes / intercepts
// positions [l,r) of ord hold elements with rank in [l,r), sorted by index
static void rec(int l,int r){
    if(r-l==1) return;
    int mid=(l+r)/2;
    // stable partition by rank
    int a=l,b=mid;
    for(int k=l;k<r;k++){ if(rk[ord[k]]<mid) tmp[a++]=ord[k]; else tmp[b++]=ord[k]; }
    // tmp[l..mid) left by index, tmp[mid..r) right by index; ord[l..r) still merged by index
    vector<int> merged(ord.begin()+l,ord.begin()+r);
    for(int k=l;k<r;k++) ord[k]=tmp[k];
    rec(l,mid);
    // cross: lines from left (rank<mid), queries right, in index order
    int head=0,sz=0;
    for(int idx:merged){
        if(rk[idx]<mid){
            if(dp[idx]>=INF) continue;
            ll m=-2LL*idx, c=dp[idx]+(ll)idx*idx;
            while(sz-head>=2){
                // remove last if unnecessary: lines (m1,c1),(m2,c2),(m,c), slopes decreasing
                ll m1=hs[sz-2],c1=hi[sz-2],m2=hs[sz-1],c2=hi[sz-1];
                if((LL)(c2-c1)*(m2-m)>=(LL)(c-c2)*(m1-m2)) sz--; else break;
            }
            hs[sz]=m;hi[sz]=c;sz++;
        } else {
            if(sz==head) continue;
            ll x=idx-1;
            while(sz-head>=2 && hs[head+1]*x+hi[head+1]<=hs[head]*x+hi[head]) head++;
            ll v=hs[head]*x+hi[head]+x*x;
            if(v<dp[idx]) dp[idx]=v;
        }
    }
    rec(mid,r);
}
int main(){
    scanf("%d",&n); int N=n+2; vector<int> h(N); h[0]=-1; h[n+1]=INT_MAX;
    for(int i=1;i<=n;i++) scanf("%d",&h[i]);
    vector<int> byh(N); iota(byh.begin(),byh.end(),0);
    stable_sort(byh.begin(),byh.end(),[&](int a,int b){return h[a]<h[b];});
    rk.resize(N); for(int i=0;i<N;i++) rk[byh[i]]=i;
    dp.assign(N,INF); dp[0]=0; ord.resize(N); iota(ord.begin(),ord.end(),0); tmp.resize(N);
    hs.resize(N);hi.resize(N);
    rec(0,N);
    printf("%lld\n",dp[n+1]);
}
