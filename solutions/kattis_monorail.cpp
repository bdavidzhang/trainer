#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// Batches alternate direction. A batch starting when the tunnel clears at time T takes all
// trains of its direction that have arrived by T (free to include), then either stops
// ("saturated", tunnel clears at T+d) or is extended to end with some later train q
// (tunnel clears at arr[q]+d, a "reset" state determined by (i,j,dir)).
// Saturated-chain states are determined by (reset train, number of steps) => O(n^2) states.
int cntv[2]; vector<ll> arr[2], pre[2]; ll d;
vector<ll> R[2]; // reset memo: R[dir][i*(b+1)+j]
unordered_map<ll,ll> chain;
const ll INF=LLONG_MAX/4;
ll f(int i,int j,ll T,int dir,bool reset){
    // i trains of N(0) done, j of S(1) done, tunnel clear at T, next batch is direction dir
    int a=cntv[0],b=cntv[1];
    if(i==a&&j==b) return 0;
    ll *slot; 
    if(reset) slot=&R[dir][(ll)i*(b+1)+j];
    else {
        ll key=((((ll)T)<<9|i)<<9|j)<<1|dir;
        auto it=chain.find(key);
        if(it!=chain.end()) return it->second;
        slot=nullptr;
        // compute then insert
        int cur=dir?j:i, tot=cntv[dir];
        ll res=INF;
        if(cur<tot){
            int p=upper_bound(arr[dir].begin(),arr[dir].end(),T)-arr[dir].begin();
            if(p<cur)p=cur;
            ll c=(ll)(p-cur)*T-(pre[dir][p]-pre[dir][cur]);
            if(p>cur){ ll r=dir?f(i,p,T+d,0,false):f(p,j,T+d,1,false); if(r<INF)res=min(res,c+r);}
            for(int q=p+1;q<=tot;q++){ ll r=dir?f(i,q,arr[1][q-1]+d,0,true):f(q,j,arr[0][q-1]+d,1,true); if(r<INF)res=min(res,c+r);}
        }
        chain[key]=res; return res;
    }
    if(*slot!=-1) return *slot;
    int cur=dir?j:i, tot=cntv[dir];
    ll res=INF;
    if(cur<tot){
        int p=upper_bound(arr[dir].begin(),arr[dir].end(),T)-arr[dir].begin();
        if(p<cur)p=cur;
        ll c=(ll)(p-cur)*T-(pre[dir][p]-pre[dir][cur]);
        if(p>cur){ ll r=dir?f(i,p,T+d,0,false):f(p,j,T+d,1,false); if(r<INF)res=min(res,c+r);}
        for(int q=p+1;q<=tot;q++){ ll r=dir?f(i,q,arr[1][q-1]+d,0,true):f(q,j,arr[0][q-1]+d,1,true); if(r<INF)res=min(res,c+r);}
    }
    slot=&R[dir][(ll)i*(b+1)+j];
    *slot=res; return res;
}
int main(){
    int n; scanf("%d %lld",&n,&d);
    for(int i=0;i<n;i++){char s[4]; ll t; scanf("%s %lld",s,&t); arr[s[0]=='S'].push_back(t);}
    for(int k=0;k<2;k++){cntv[k]=arr[k].size(); pre[k].assign(cntv[k]+1,0); for(int i=0;i<cntv[k];i++)pre[k][i+1]=pre[k][i]+arr[k][i];}
    for(int k=0;k<2;k++) R[k].assign((ll)(cntv[0]+1)*(cntv[1]+1),-1);
    chain.reserve(1<<20);
    // initial states: nothing done, T=-1 (before any arrival); (0,0,dir) reset slots are unused otherwise
    ll ans=min(f(0,0,-1,0,true),f(0,0,-1,1,true));
    printf("%lld\n",ans);
}
