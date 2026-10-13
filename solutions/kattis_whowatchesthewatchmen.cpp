#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;
typedef array<ll,3> V;
V sub(const V&a,const V&b){ return {a[0]-b[0],a[1]-b[1],a[2]-b[2]}; }
V cross(const V&a,const V&b){ return {a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]}; }
ll dot(const V&a,const V&b){ return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]; }
LL dot128(const V&a,const V&b){ return (LL)a[0]*b[0]+(LL)a[1]*b[1]+(LL)a[2]*b[2]; }
bool isz(const V&a){ return !a[0]&&!a[1]&&!a[2]; }
ll gcdll(ll a,ll b){ a=llabs(a);b=llabs(b); while(b){ll t=a%b;a=b;b=t;} return a; }
V norm(V a){ ll g=gcdll(gcdll(a[0],a[1]),a[2]); return {a[0]/g,a[1]/g,a[2]/g}; }
int n; vector<V> p,v;

int hungarian(const vector<vector<int>>&a){ // a is 1-indexed n x n, returns min cost
    const int INF=INT_MAX/2;
    vector<int> u(n+1),w(n+1),pp(n+1),way(n+1);
    for(int i=1;i<=n;i++){
        pp[0]=i; int j0=0; vector<int> minv(n+1,INF); vector<char> used(n+1,0);
        do{
            used[j0]=1; int i0=pp[j0],delta=INF,j1=0;
            for(int j=1;j<=n;j++) if(!used[j]){
                int cur=a[i0][j]-u[i0]-w[j];
                if(cur<minv[j]){minv[j]=cur;way[j]=j0;}
                if(minv[j]<delta){delta=minv[j];j1=j;}
            }
            for(int j=0;j<=n;j++) if(used[j]){u[pp[j]]+=delta;w[j]-=delta;} else minv[j]-=delta;
            j0=j1;
        }while(pp[j0]!=0);
        do{ int j1=way[j0]; pp[j0]=pp[j1]; j0=j1; }while(j0);
    }
    return -w[0];
}
int main(){
    scanf("%d",&n);
    p.resize(n); v.resize(n);
    for(int i=0;i<n;i++) scanf("%lld %lld %lld %lld %lld %lld",&p[i][0],&p[i][1],&p[i][2],&v[i][0],&v[i][1],&v[i][2]);
    if(n==1){ puts("-1"); return 0; }
    bool col=true;
    V u=sub(p[1],p[0]);
    for(int i=2;i<n;i++) if(!isz(cross(sub(p[i],p[0]),u))) col=false;
    if(!col){
        const int BIG=1000000;
        vector<vector<int>> a(n+1,vector<int>(n+1,BIG));
        for(int i=0;i<n;i++){
            map<V,pair<ll,int>> near;
            for(int j=0;j<n;j++) if(j!=i){
                V d=sub(p[j],p[i]); ll g=gcdll(gcdll(d[0],d[1]),d[2]);
                V k={d[0]/g,d[1]/g,d[2]/g};
                auto it=near.find(k);
                if(it==near.end()||it->second.first>g) near[k]={g,j};
            }
            V vi=norm(v[i]);
            for(auto&kv:near) a[i+1][kv.second.second+1]= (kv.first==vi)?0:1;
        }
        int r=hungarian(a);
        printf("%d\n", r>=BIG?-1:r);
        return 0;
    }
    // collinear
    vector<int> ord(n); iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int a,int b){ return dot(p[a],u)<dot(p[b],u); });
    vector<int> nR(n),nL(n),par(n); // nR: 1 if not facing +u along the line
    for(int i=0;i<n;i++){
        bool pl=isz(cross(v[i],u)); ll d=dot(v[i],u);
        par[i]=pl; nR[i]=!(pl&&d>0); nL[i]=!(pl&&d<0);
    }
    if(n%2==0){
        int c=0;
        for(int i=0;i<n;i+=2) c+=nR[ord[i]]+nL[ord[i+1]];
        printf("%d\n",c); return 0;
    }
    V mu={-u[0],-u[1],-u[2]};
    // cost for moved sentry m plus sentry b (last on-line sentry of the cycle, looking at m); w = direction of (a-b)
    auto joint=[&](int m,int b,const V&w)->int{
        if(par[m]||par[b]) return par[m]+par[b];
        V c=cross(v[m],v[b]);
        if(isz(c)) return 1;
        if(dot128(w,c)!=0) return 1;
        V c1=cross(w,v[b]), c2=cross(w,v[m]);
        LL t=dot128(c1,c), s=-dot128(c2,c);
        return (t>0&&s>0)?0:1;
    };
    int best=INT_MAX, k=n-1;
    vector<int> R(k),pre(k+1),suf(k+2),sr(k+1),sl(k+1),jr(k),jl(k);
    for(int mi=0;mi<n;mi++){
        int m=ord[mi];
        for(int i=0,t=0;i<n;i++) if(i!=mi) R[t++]=ord[i];
        pre[0]=0; for(int i=0;i+1<k;i+=2) pre[i+2]=pre[i]+nR[R[i]]+nL[R[i+1]];
        suf[k]=0; for(int i=k-2;i>=0;i-=2) suf[i]=suf[i+2]+nR[R[i]]+nL[R[i+1]];
        sr[0]=sl[0]=0; for(int i=0;i<k;i++){ sr[i+1]=sr[i]+nR[R[i]]; sl[i+1]=sl[i]+nL[R[i]]; }
        for(int i=0;i<k;i++){ jr[i]=joint(m,R[i],mu); jl[i]=joint(m,R[i],u); }
        for(int l=0;l<k;l+=2) for(int r=l+1;r<k;r+=2){
            int base=pre[l]+suf[r+1];
            int c1=base+(sr[r]-sr[l])+jr[r];        // a=l walks right to b=r
            int c2=base+(sl[r+1]-sl[l+1])+jl[l];    // a=r walks left to b=l
            best=min(best,min(c1,c2));
        }
    }
    printf("%d\n",1000+best);
}
