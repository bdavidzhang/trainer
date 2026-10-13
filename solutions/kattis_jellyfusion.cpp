#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int C=1000000;
struct LiChao{
    vector<ll> m,c; int sz;
    void init(){ sz=1; while(sz<C+1)sz<<=1; m.assign(2*sz,0); c.assign(2*sz,LLONG_MIN/4); }
    void add(ll a,ll b){
        int node=1,lo=0,hi=sz-1;
        while(true){
            int mid=(lo+hi)/2;
            bool lf=a*lo+b>m[node]*lo+c[node];
            bool md=a*mid+b>m[node]*mid+c[node];
            if(md){swap(a,m[node]);swap(b,c[node]);}
            if(lo==hi)break;
            if(lf!=md){node=2*node;hi=mid;}
            else {node=2*node+1;lo=mid+1;}
        }
    }
    ll query(int x){
        int node=1,lo=0,hi=sz-1; ll r=LLONG_MIN;
        while(true){
            r=max(r,m[node]*x+c[node]);
            if(lo==hi)break;
            int mid=(lo+hi)/2;
            if(x<=mid){node=2*node;hi=mid;}else{node=2*node+1;lo=mid+1;}
        }
        return r;
    }
};
LiChao A,B;
ll solve(const vector<ll>&h,const vector<ll>&w){
    int n=h.size();
    A.init();B.init();
    ll dp=0;
    for(int i=0;i<n;i++){
        A.add(h[i],dp); B.add(w[i],dp);
        dp=max(A.query((int)w[i]),B.query((int)h[i]));
    }
    return dp;
}
int main(){
    int n; scanf("%d",&n);
    vector<ll> h(n),w(n);
    for(int i=0;i<n;i++)scanf("%lld %lld",&h[i],&w[i]);
    int p=max_element(h.begin(),h.end())-h.begin();
    ll best=0;
    for(int t=0;t<2;t++){
        int st=(p+t)%n; // cut just before p (t=0) or just after p (t=1)
        vector<ll> hh(n),ww(n);
        for(int i=0;i<n;i++){hh[i]=h[(st+i)%n];ww[i]=w[(st+i)%n];}
        best=max(best,solve(hh,ww));
    }
    printf("%lld\n",best);
}
