#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,k,w;
struct E{int a,b,c;};
vector<E> sp,ns; vector<int> par;
int fnd(int x){while(par[x]!=x){par[x]=par[par[x]];x=par[x];}return x;}
// returns special count; cost includes lambda; edges used in used
int run(int lam,ll&cost,int&used){
    for(int i=0;i<=n;i++)par[i]=i;
    size_t i=0,j=0; int cnt=0; cost=0; used=0;
    while(i<sp.size()||j<ns.size()){
        bool takeS;
        if(i>=sp.size()) takeS=false; else if(j>=ns.size()) takeS=true;
        else takeS = sp[i].c+lam<=ns[j].c;
        const E&e = takeS?sp[i++]:ns[j++];
        int x=fnd(e.a),y=fnd(e.b); if(x==y) continue;
        par[x]=y; used++;
        if(takeS){cnt++;cost+=e.c+lam;} else cost+=e.c;
    }
    return cnt;
}
int main(){
    scanf("%d %d %d %d",&n,&m,&k,&w);
    vector<char> isS(n+1,0);
    for(int i=0;i<k;i++){int s;scanf("%d",&s);isS[s]=1;}
    for(int i=0;i<m;i++){E e;scanf("%d %d %d",&e.a,&e.b,&e.c); if(isS[e.a]!=isS[e.b]) sp.push_back(e); else ns.push_back(e);}
    auto cmp=[](const E&x,const E&y){return x.c<y.c;};
    sort(sp.begin(),sp.end(),cmp); sort(ns.begin(),ns.end(),cmp);
    par.resize(n+1);
    ll cost; int used;
    const int B=200005;
    int mx=run(-B,cost,used);
    if(used!=n-1){puts("-1");return 0;}
    int mn=run(B,cost,used);
    if(w<mn||w>mx){puts("-1");return 0;}
    int lo=-B,hi=B; // largest lam with cnt>=w
    while(lo<hi){
        int mid=lo+(hi-lo+1)/2;
        if(run(mid,cost,used)>=w) lo=mid; else hi=mid-1;
    }
    run(lo,cost,used);
    printf("%lld\n",cost-(ll)lo*w);
}
