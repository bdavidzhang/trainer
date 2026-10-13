#include <bits/stdc++.h>
using namespace std;
// node 2*i = "i fires horizontally", 2*i+1 = "i fires vertically".
// Same row, distance <= 2P: H_i -> V_j.  Same column, distance <= 2P: V_i -> H_j.
// The implication graph is symmetric under contraposition, edges are enumerated implicitly.
int n; vector<int> X,Y;
vector<int> ord[2];          // points sorted by (y,x) and by (x,y)
vector<int> pos[2];
int idx_[8005],low_[8005],comp_[8005],timer_,ncomp; bool onst[8005]; vector<int> stk;
long long lim;
template<class F> void nbrs(int u,F f){
    int i=u>>1,t=u&1; // t=0: H -> row neighbours become V ; t=1: V -> column neighbours become H
    const vector<int>&o=ord[t]; int p=pos[t][i];
    for(int q=p-1;q>=0;q--){int j=o[q];
        if(t==0){ if(Y[j]!=Y[i]||X[i]-X[j]>lim)break; } else { if(X[j]!=X[i]||Y[i]-Y[j]>lim)break; }
        f(2*j+(1-t)); }
    for(int q=p+1;q<n;q++){int j=o[q];
        if(t==0){ if(Y[j]!=Y[i]||X[j]-X[i]>lim)break; } else { if(X[j]!=X[i]||Y[j]-Y[i]>lim)break; }
        f(2*j+(1-t)); }
}
void dfs(int u){
    idx_[u]=low_[u]=++timer_; stk.push_back(u); onst[u]=true;
    nbrs(u,[&](int v){
        if(!idx_[v]){dfs(v); low_[u]=min(low_[u],low_[v]);}
        else if(onst[v]) low_[u]=min(low_[u],idx_[v]);
    });
    if(low_[u]==idx_[u]){
        while(true){int v=stk.back();stk.pop_back();onst[v]=false;comp_[v]=ncomp; if(v==u)break;}
        ncomp++;
    }
}
bool ok(long long P){
    lim=2*P; timer_=0; ncomp=0;
    for(int i=0;i<2*n;i++){idx_[i]=0;onst[i]=false;}
    for(int i=0;i<2*n;i++)if(!idx_[i])dfs(i);
    for(int i=0;i<n;i++)if(comp_[2*i]==comp_[2*i+1])return false;
    return true;
}
int main(){
    scanf("%d",&n); X.resize(n);Y.resize(n);
    for(int i=0;i<n;i++)scanf("%d %d",&X[i],&Y[i]);
    for(int t=0;t<2;t++){ord[t].resize(n);iota(ord[t].begin(),ord[t].end(),0);pos[t].resize(n);}
    sort(ord[0].begin(),ord[0].end(),[&](int a,int b){return make_pair(Y[a],X[a])<make_pair(Y[b],X[b]);});
    sort(ord[1].begin(),ord[1].end(),[&](int a,int b){return make_pair(X[a],Y[a])<make_pair(X[b],Y[b]);});
    for(int t=0;t<2;t++)for(int q=0;q<n;q++)pos[t][ord[t][q]]=q;
    if(ok(500000)){puts("UNLIMITED");return 0;}
    long long lo=0,hi=500000; // ok(lo), !ok(hi)
    while(hi-lo>1){long long m=(lo+hi)/2; if(ok(m))lo=m; else hi=m;}
    printf("%lld\n",lo);
}
