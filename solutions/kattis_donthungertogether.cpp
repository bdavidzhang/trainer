#include <bits/stdc++.h>
using namespace std;
static int gc(){static char b[1<<16];static size_t p=0,l=0;if(p==l){l=fread(b,1,sizeof b,stdin);p=0;if(!l)return -1;}return b[p++];}
static int rd(){int c=gc();while(c<'0'||c>'9')c=gc();int x=0;while(c>='0'&&c<='9'){x=x*10+c-'0';c=gc();}return x;}
int n,k;
vector<long long> q;vector<int> f,par;vector<double> rem_;
int fnd(int x){while(par[x]!=x){par[x]=par[par[x]];x=par[x];}return x;}
// nights 1..n; par index j -> largest unfilled night <= j (0 = none)
bool ok(double T){
    for(int i=0;i<=n;i++){par[i]=i;rem_[i]=T;}
    int filled=0;
    for(int i=n;i>=1;i--){
        double a=(double)q[i];
        int j=fnd(f[i]);
        while(a>0&&j>=i){
            if(a>=rem_[j]){a-=rem_[j];rem_[j]=0;filled++;par[j]=j-1;j=fnd(j);}
            else{rem_[j]-=a;a=0;}
        }
    }
    return filled==n;
}
int main(){
    n=rd();k=rd();
    q.resize(n+1);f.resize(n+1);par.resize(n+2);rem_.resize(n+2);
    vector<int> d(n+2,0);long long tot=0;
    for(int i=1;i<=n;i++){q[i]=rd();f[i]=rd();tot+=q[i];if(q[i]>0){d[i]++;d[f[i]+1]--;}}
    int c=0;
    for(int i=1;i<=n;i++){c+=d[i];if(c<=0){puts("-1");return 0;}}
    // T=1/n is always feasible when every night is covered by some positive food
    double lo=1.0/n,hi=(double)tot/n*1.000001+1e-9;
    while(hi/lo>2){double m=sqrt(lo*hi);if(ok(m))lo=m;else hi=m;}
    for(int it=0;it<34;it++){double m=(lo+hi)/2;if(ok(m))lo=m;else hi=m;}
    lo=(lo+hi)/2;
    printf("%.12f\n",lo/k);
}
