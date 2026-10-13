#include <bits/stdc++.h>
using namespace std;
// Stations are optimal at metropolitan areas (utility is convex between consecutive areas).
// Contributions at distance > T are negligible, so each station pair closer than 2T is handled
// exactly, farther pairs decompose into independent truncated tails. Lagrangian (Aliens) on k.
static const int T=50;
int n,k;
vector<int> p; vector<long long> d;
vector<double> Lt,Rt;
vector<int> nearStart; // first i with d[j]-d[i] < 2T
vector<int> off; vector<double> cst; // cst[off[j]+ (i-nearStart[j])] = c(i,j)
vector<double> dp; vector<int> cnt;
pair<double,int> run(double lam){
    // far candidates: prefix max of dp[i]+Rt[i] for i<nearStart[j]
    double bestFar=-1e300; int bestFarCnt=0; int fp=0;
    double res=-1e300; int rc=0;
    for(int j=0;j<n;j++){
        while(fp<nearStart[j]){ double v=dp[fp]+Rt[fp]; if(v>bestFar){bestFar=v;bestFarCnt=cnt[fp];} fp++; }
        double best=Lt[j]; int bc=0;
        if(fp>0 && bestFar+Lt[j]>best){best=bestFar+Lt[j];bc=bestFarCnt;}
        const double*c=&cst[off[j]]; int s=nearStart[j];
        for(int i=s;i<j;i++){ double v=dp[i]+c[i-s]; if(v>best){best=v;bc=cnt[i];} }
        dp[j]=best+p[j]-lam; cnt[j]=bc+1;
        double v=dp[j]+Rt[j]; if(v>res){res=v;rc=cnt[j];}
    }
    return {res,rc};
}
int main(){
    scanf("%d %d",&n,&k);
    p.resize(n); d.resize(n);
    long long tot=0;
    for(int i=0;i<n;i++){scanf("%d %lld",&p[i],&d[i]);tot+=p[i];}
    if(k>=n){printf("%.9f\n",(double)tot);return 0;}
    vector<double> p2(4*T+5); for(int i=0;i<(int)p2.size();i++) p2[i]=pow(2.0,-(double)i);
    Lt.assign(n,0); Rt.assign(n,0);
    for(int i=0;i<n;i++){
        for(int t=i+1;t<n&&d[t]-d[i]<=T;t++) Rt[i]+=p[t]*p2[d[t]-d[i]];
        for(int t=i-1;t>=0&&d[i]-d[t]<=T;t--) Lt[i]+=p[t]*p2[d[i]-d[t]];
    }
    nearStart.assign(n,0); off.assign(n+1,0);
    {int s=0; for(int j=0;j<n;j++){ while(d[j]-d[s]>=2*T) s++; nearStart[j]=s; off[j+1]=off[j]+(j-s);} }
    cst.assign(off[n],0);
    // for each i, compute c(i,j) for near j>i
    {
        vector<double> A,Bv;
        for(int i=0;i<n;i++){
            A.clear();Bv.clear(); A.push_back(0);Bv.push_back(0); // index t-i
            int m=i; // last index with 2*d[m] <= d[i]+d[j]
            for(int j=i+1;j<n&&d[j]-d[i]<2*T;j++){
                // prefix arrays hold up to j-1 at this point (indices i..j-1)
                while(m+1<j && 2*d[m+1]<=d[i]+d[j]) m++;
                double v=A[m-i]+p2[d[j]-d[i]]*(Bv[j-1-i]-Bv[m-i]);
                cst[off[j]+(i-nearStart[j])]=v;
                long long e=d[j]-d[i];
                A.push_back(A.back()+p[j]*p2[e]);
                Bv.push_back(Bv.back()+p[j]*ldexp(1.0,(int)e));
            }
        }
    }
    dp.assign(n,0); cnt.assign(n,0);
    double lo=0,hi=101; double ans=1e300;
    for(int it=0;it<60;it++){
        double mid=(lo+hi)/2;
        auto r=run(mid);
        ans=min(ans,r.first+mid*k);
        if(r.second>k) lo=mid; else hi=mid;
    }
    printf("%.9f\n",ans);
}
