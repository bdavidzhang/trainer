#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// Reduce w = q*d + r. Job i has in-value A_i = f_i and out-value B_i = (f_i + r) mod d.
// T = B_last - r + d*(H + D) + (N-1)*q*d, H = #{f_i + r >= d}, D = #descents (A_next < B_cur) on the path.
// Add a dummy node (B = 0, A = beta) to turn the path into a Hamiltonian cycle whose closing link is free iff B_last <= beta.
// Min descents of a Hamiltonian cycle = delta or delta+1, where delta = max deficiency over thresholds,
// and +1 iff the "zone graph" (zones between tight thresholds, each node joining zone(A) and zone(B)) is disconnected.
int n;
vector<ll> A,B;
vector<int> par;
int fnd(int x){while(par[x]!=x){par[x]=par[par[x]];x=par[x];}return x;}
ll cyc(){
    int m0=A.size();
    vector<ll> vals(A);vals.insert(vals.end(),B.begin(),B.end());
    sort(vals.begin(),vals.end());vals.erase(unique(vals.begin(),vals.end()),vals.end());
    int m=vals.size();
    if(m==1)return 0;
    vector<int> ia(m0),ib(m0);
    vector<int> e(m+1,0);
    for(int i=0;i<m0;i++){
        ia[i]=lower_bound(vals.begin(),vals.end(),A[i])-vals.begin();
        ib[i]=lower_bound(vals.begin(),vals.end(),B[i])-vals.begin();
        e[ia[i]]++;e[ib[i]]--;
    }
    for(int k=m-1;k>=0;k--)e[k]+=e[k+1]; // e[k] = #A>=vals[k] - #B>=vals[k]
    int delta=0;
    for(int k=1;k<m;k++)delta=max(delta,-e[k]);
    vector<int> zone(m,0);int z=0;
    for(int k=1;k<m;k++){if(e[k]==-delta)z++;zone[k]=z;}
    par.resize(z+1);iota(par.begin(),par.end(),0);
    int comp=z+1;
    auto uni=[&](int a,int b){a=fnd(a);b=fnd(b);if(a!=b){par[a]=b;comp--;}};
    if(delta>=1&&z>=1)uni(z,0);
    for(int i=0;i<m0;i++)uni(zone[ia[i]],zone[ib[i]]);
    return comp==1?delta:delta+1;
}
int main(){
    ll w,d;
    scanf("%d %lld %lld",&n,&w,&d);
    vector<ll> f(n);for(auto&x:f)scanf("%lld",&x);
    ll q=w/d,r=w%d;
    A.resize(n+1);B.resize(n+1);
    ll H=0;
    for(int i=0;i<n;i++){A[i]=f[i];B[i]=(f[i]+r)%d;if(f[i]+r>=d)H++;}
    B[n]=0;A[n]=d;
    ll D=cyc();
    vector<ll> bs(B.begin(),B.begin()+n);
    sort(bs.begin(),bs.end());bs.erase(unique(bs.begin(),bs.end()),bs.end());
    int lo=0,hi=bs.size()-1;
    while(lo<hi){
        int mid=(lo+hi)/2;
        A[n]=bs[mid];
        if(cyc()==D)hi=mid;else lo=mid+1;
    }
    ll T=bs[lo]-r+d*(H+D)+(ll)(n-1)*q*d;
    printf("%lld\n",T);
}
