#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N; vector<ll> cx,cy,cr; int cur; ll px,py;
struct Arc{int id; bool up;};
// is current point strictly below arc a?
static bool ptBelow(const Arc&a){
    ll dx=px-cx[a.id]; ll R2=cr[a.id]*cr[a.id]-dx*dx; ll dy=py-cy[a.id];
    if(a.up) return dy<0||dy*dy<R2;
    return dy<0&&dy*dy>R2;
}
struct Cmp{ bool operator()(const Arc&a,const Arc&b)const{
    if(a.id==b.id) return !a.up&&b.up;
    if(a.id==cur) return ptBelow(b);
    if(b.id==cur) return !ptBelow(a);
    return false;
}};
int main(){
    int n,q; scanf("%d %d",&n,&q); N=n+q; cx.resize(N);cy.resize(N);cr.resize(N);
    for(int i=0;i<N;i++)scanf("%lld %lld %lld",&cx[i],&cy[i],&cr[i]);
    vector<array<ll,3>> ev; // x, type(0 insert,1 remove), id
    for(int i=0;i<N;i++){ev.push_back({cx[i]-cr[i],0,i});ev.push_back({cx[i]+cr[i],1,i});}
    sort(ev.begin(),ev.end());
    set<Arc,Cmp> S; vector<set<Arc,Cmp>::iterator> itU(N),itL(N); vector<int> par(N,-1);
    for(auto&e:ev){ int i=e[2];
        if(e[1]==0){ cur=i; px=cx[i]-cr[i]; py=cy[i];
            itL[i]=S.insert(Arc{i,false}).first; itU[i]=S.insert(Arc{i,true}).first;
            auto nx=next(itU[i]);
            if(nx==S.end())par[i]=-1; else if(nx->up)par[i]=nx->id; else par[i]=par[nx->id];
        } else { S.erase(itL[i]); S.erase(itU[i]); }
    }
    vector<int> ord(N); iota(ord.begin(),ord.end(),0); sort(ord.begin(),ord.end(),[&](int a,int b){return cr[a]<cr[b];});
    vector<ll> sm(N,0),s0(N,0),ans(N,0);
    for(int v:ord){ int p=par[v];
        if(v<n){ ll f0=sm[v],f1=1+s0[v]; if(p>=0){sm[p]+=max(f0,f1);s0[p]+=f0;} }
        else { ans[v]=max(sm[v],1+s0[v]); if(p>=0){sm[p]+=sm[v];s0[p]+=s0[v];} }
    }
    for(int i=n;i<N;i++)printf("%lld\n",ans[i]);
}
