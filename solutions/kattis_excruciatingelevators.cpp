#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// Elevator with phase a is at floor 0 at times == a (mod L), L = 2M; it passes floor f at times a+f (up), a-f (down).
// Exchange argument: some optimal configuration has an "anchor tree": one elevator has phase 0, and every other
// elevator e' has a zero-wait boarding at some floor f_j right after an arrival by another elevator e, which gives
// a_e' - a_e in {t_j, t_j - 2 f_j, t_j + 2 f_j} (mod L). Enumerate the 4 rooted tree shapes on 4 elevators and all
// offsets, simulate greedily (earliest arrival) each time.
int M=1000000, L;
int n;
int F[40], RU[40], RD[40], TM[40]; // per move: start floor, ride cost boarding up / down, work time at dest mod L
ll remLB[41];
ll best;
int K; // number of elevators in use
static inline ll sim(const int*a,int k){
    int u=0; ll tot=0;
    for(int j=0;j<n;j++){
        if(tot+remLB[j]>=best) return LLONG_MAX;
        int f=F[j]; int bc=INT_MAX;
        for(int e=0;e<k;e++){
            int x=u-a[e]; if(x<0)x+=L;
            int d1=f-x; if(d1<0)d1+=L;
            int d2=L-f-x; if(d2<0)d2+=L;
            int c1=d1+RU[j], c2=d2+RD[j];
            int c=c1<c2?c1:c2;
            if(c<bc)bc=c;
        }
        tot+=bc;
        u=(int)(((ll)u+bc+TM[j])%L);
    }
    return tot;
}
int main(int argc,char**argv){
    if(argc>1)M=atoi(argv[1]);
    if(argc>2)K=atoi(argv[2]); else K=4;
    L=2*M;
    scanf("%d",&n);
    vector<ll> f(n+1),t(n+1);
    f[0]=0;t[0]=0;
    for(int i=1;i<=n;i++)scanf("%lld",&f[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&t[i]);
    ll sumT=0;
    for(int j=0;j<n;j++){
        int a=f[j],b=f[j+1];
        F[j]=a;
        RU[j]= b>a ? b-a : L-a-b;
        RD[j]= b<a ? a-b : a+b;
        TM[j]=(int)(t[j+1]%L);
        sumT+=t[j+1];
    }
    remLB[n]=0;
    for(int j=n-1;j>=0;j--)remLB[j]=remLB[j+1]+llabs(f[j+1]-f[j]);
    vector<int> D;
    for(int j=1;j<n;j++){
        ll tt=t[j]%L;
        for(ll o:{tt,tt+2*f[j],tt-2*f[j]}) D.push_back((int)(((o%L)+L)%L));
    }
    sort(D.begin(),D.end());D.erase(unique(D.begin(),D.end()),D.end());
    int m=D.size();
    best=LLONG_MAX;
    int a[4]={0,0,0,0};
    auto upd=[&](int k){ ll v=sim(a,k); if(v<best)best=v; };
    auto add=[&](int x,int d){int r=x+d; if(r>=L)r-=L; return r;};
    upd(1);
    if(K>=2) for(int i=0;i<m;i++){a[1]=D[i];upd(2);}
    if(K>=3) for(int i=0;i<m;i++){
        a[1]=D[i];
        for(int j=i;j<m;j++){a[2]=D[j];upd(3);}
        for(int j=0;j<m;j++){a[2]=add(a[1],D[j]);upd(3);}
    }
    if(K>=4) for(int i=0;i<m;i++){
        a[1]=D[i];
        for(int j=0;j<m;j++){
            // star: 2,3,4 children of 1
            if(j>=i){ a[2]=D[j]; for(int k=j;k<m;k++){a[3]=D[k];upd(4);} }
            // chain 1->2->3->4 and 1->2->3, 2->4
            a[2]=add(a[1],D[j]);
            for(int k=0;k<m;k++){a[3]=add(a[2],D[k]);upd(4);}
            for(int k=j;k<m;k++){a[3]=add(a[1],D[k]);upd(4);}
            // 1->2, 1->3, 3->4
            a[2]=D[j];
            for(int k=0;k<m;k++){a[3]=add(a[2],D[k]);upd(4);}
        }
    }
    printf("%lld\n",best+sumT);
}
