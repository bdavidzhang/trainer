#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
struct P{ ld x,y; };
int main(){
    int a; scanf("%d",&a); vector<P> A(a); for(auto&p:A){ double x,y; scanf("%lf %lf",&x,&y); p={x,y}; }
    int b; scanf("%d",&b); vector<P> B(b); for(auto&p:B){ double x,y; scanf("%lf %lf",&x,&y); p={x,y}; }
    int n=b;
    // param of intersection of line (p,q) [t: p+t(q-p)] with line (u,v); returns false if parallel
    auto inter=[&](P p,P q,P u,P v,ld&t){
        ld dx=q.x-p.x,dy=q.y-p.y,ex=v.x-u.x,ey=v.y-u.y;
        ld den=dx*ey-dy*ex; if(fabsl(den)<1e-18L) return false;
        t=((u.x-p.x)*ey-(u.y-p.y)*ex)/den; return true;
    };
    vector<ld> len(n),alo(n),ahi(n);
    vector<vector<ld>> T(n,vector<ld>(n,0)); vector<vector<char>> ok(n,vector<char>(n,0));
    for(int k=0;k<n;k++){
        P p=B[k],q=B[(k+1)%n];
        len[k]=sqrtl((q.x-p.x)*(q.x-p.x)+(q.y-p.y)*(q.y-p.y));
        ld lo=-1e30L,hi=1e30L;
        for(int i=0;i<a;i++){ ld t; if(inter(p,q,A[i],A[(i+1)%a],t)){ if(t>=0.5L) hi=min(hi,t); else lo=max(lo,t);} }
        alo[k]=lo; ahi[k]=hi;
        for(int j=0;j<n;j++) if(j!=k){ ld t; if(inter(p,q,B[j],B[(j+1)%n],t)){ ok[k][j]=1; T[k][j]=t; } }
    }
    auto cost=[&](int k,int l,int r){
        ld lo=alo[k],hi=ahi[k];
        int js[2]={l,r};
        for(int z=0;z<2;z++){ int j=js[z]; if(ok[k][j]){ ld t=T[k][j]; if(t>=0.5L) hi=min(hi,t); else lo=max(lo,t);} }
        return (hi-lo)*len[k];
    };
    // dp[l][d]: edges strictly between l and l+d (cyclic), both ends already cut
    vector<vector<ld>> dp(n,vector<ld>(n+1,0));
    for(int d=2;d<=n;d++) for(int l=0;l<n;l++){
        int r=(l+d)%n; ld best=1e30L;
        for(int e=1;e<d;e++){ int k=(l+e)%n; ld c=cost(k,l,r)+dp[l][e]+dp[k][d-e]; if(c<best) best=c; }
        dp[l][d]=best;
    }
    ld ans=1e30L;
    for(int i=0;i<n;i++) ans=min(ans,(ahi[i]-alo[i])*len[i]+dp[i][n]);
    printf("%.10Lf\n",ans);
}
