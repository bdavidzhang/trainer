#include <bits/stdc++.h>
using namespace std;
int n; vector<string> g; int cnt[10][10]; int sol[8][8];
int par[100], sz_[100];
int fnd(int x){ while(par[x]!=x) x=par[x]; return x; }
int vid(int i,int j){ return i*(n+1)+j; }
// vertex (vi,vj) feasibility after cell index cur has been decided
bool okv(int vi,int vj,int cur){
    char c=g[vi][vj]; if(c=='+') return true;
    int need=c-'0', rem=0;
    for(int di=-1;di<=0;di++) for(int dj=-1;dj<=0;dj++){
        int ci=vi+di,cj=vj+dj;
        if(ci<0||cj<0||ci>=n||cj>=n) continue;
        if(ci*n+cj>cur) rem++;
    }
    return cnt[vi][vj]<=need && cnt[vi][vj]+rem>=need;
}
bool rec(int cur){
    if(cur==n*n) return true;
    int i=cur/n,j=cur%n;
    for(int t=0;t<2;t++){
        int ai,aj,bi,bj;
        if(t==0){ai=i;aj=j;bi=i+1;bj=j+1;} else {ai=i;aj=j+1;bi=i+1;bj=j;}
        int ra=fnd(vid(ai,aj)), rb=fnd(vid(bi,bj));
        if(ra==rb) continue;
        cnt[ai][aj]++; cnt[bi][bj]++;
        bool ok=okv(i,j,cur)&&okv(i,j+1,cur)&&okv(i+1,j,cur)&&okv(i+1,j+1,cur);
        if(ok){
            if(sz_[ra]<sz_[rb]) swap(ra,rb);
            par[rb]=ra; sz_[ra]+=sz_[rb];
            sol[i][j]=t;
            if(rec(cur+1)) return true;
            par[rb]=rb; sz_[ra]-=sz_[rb];
        }
        cnt[ai][aj]--; cnt[bi][bj]--;
    }
    return false;
}
int main(){
    cin>>n; g.resize(n+1); for(auto&s:g) cin>>s;
    for(int i=0;i<(n+1)*(n+1);i++){par[i]=i;sz_[i]=1;}
    rec(0);
    for(int i=0;i<n;i++){ for(int j=0;j<n;j++) putchar(sol[i][j]==0?'\\':'/'); putchar('\n'); }
}
