#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// dirs: 0=N,1=E,2=S,3=W
int n,m;
int nb[2505][4], eid[2505][4];
ll rem_[5005]; int stamp[2505][4], posIdx[2505][4]; int cntE[5005];
int main(){
    scanf("%d %d",&n,&m);
    vector<ll> x(n+1),y(n+1); for(int i=1;i<=n;i++)scanf("%lld %lld",&x[i],&y[i]);
    memset(nb,0,sizeof nb); memset(eid,-1,sizeof eid);
    for(int e=0;e<m;e++){
        int i,j; ll k; scanf("%d %d %lld",&i,&j,&k); rem_[e]=k;
        int d;
        if(x[i]==x[j]) d = y[j]>y[i]?0:2; else d = x[j]>x[i]?1:3;
        nb[i][d]=j; eid[i][d]=e; nb[j][(d+2)%4]=i; eid[j][(d+2)%4]=e;
    }
    int s; char dc; scanf("%d %c",&s,&dc);
    int d = dc=='N'?0:dc=='E'?1:dc=='S'?2:3;
    int phase=1; vector<int> path; // edges traversed in this phase
    int v=s;
    while(true){
        // traverse edge (v,d)
        int e=eid[v][d]; int u=nb[v][d];
        path.push_back(e);
        rem_[e]--;
        bool removed=false;
        if(rem_[e]==0){ eid[v][d]=-1; eid[u][(d+2)%4]=-1; removed=true; }
        v=u;
        if(removed){ phase++; path.clear(); }
        // choose next: left, straight, right
        int opts[3]={(d+3)%4,d,(d+1)%4}; int av[3],c=0;
        for(int t=0;t<3;t++) if(eid[v][opts[t]]>=0) av[c++]=opts[t];
        if(c==0)break;
        int nd = (c==3)?av[1]:av[0];
        d=nd;
        // state (v,d) about to traverse
        if(stamp[v][d]==phase){
            int st=posIdx[v][d];
            // cycle is path[st..end)
            vector<int> used;
            for(size_t i=st;i<path.size();i++){ if(cntE[path[i]]++==0) used.push_back(path[i]); }
            ll t=LLONG_MAX;
            for(int e2:used) t=min(t,(rem_[e2]-1)/cntE[e2]);
            for(int e2:used){ rem_[e2]-=t*cntE[e2]; cntE[e2]=0; }
            phase++; path.clear();
        }
        stamp[v][d]=phase; posIdx[v][d]=path.size();
    }
    printf("%lld %lld\n",x[v],y[v]);
}
