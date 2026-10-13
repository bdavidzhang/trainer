#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef unsigned long long ull;
const ll MOD=1e9+7;
typedef vector<vector<ll>> Mat;
Mat mul(const Mat&a,const Mat&b){
    int n=a.size(); Mat c(n,vector<ll>(n,0));
    for(int i=0;i<n;i++)for(int k=0;k<n;k++){ ll x=a[i][k]; if(!x)continue; for(int j=0;j<n;j++) c[i][j]=(c[i][j]+x*b[k][j])%MOD; }
    return c;
}
Mat mpow(Mat a, ll e){
    int n=a.size(); Mat r(n,vector<ll>(n,0)); for(int i=0;i<n;i++) r[i][i]=1;
    while(e){ if(e&1) r=mul(r,a); a=mul(a,a); e>>=1; }
    return r;
}
Mat base(int S){
    Mat t(S+1,vector<ll>(S+1,0));
    for(int i=0;i<=S;i++){ t[i][i]=1; if(i<S) t[i][i+1]=S-i; if(i>0) t[i][i-1]=i; }
    return t;
}
int main(){
    ll N; int P,S,C; cin>>N>>P>>S>>C;
    vector<ll> t(P); vector<char> g(P); vector<int> s(P),c(P),b(P);
    for(int i=0;i<P;i++) cin>>t[i]>>g[i]>>s[i]>>c[i]>>b[i];
    Mat BS=base(S), BC=base(C);
    int W=C+1;
    vector<ll> dp((S+1)*W,0); dp[0]=1;
    ll cur=1;
    auto step=[&](ll d){
        if(d==0) return;
        Mat A=mpow(BS,d), B=mpow(BC,d);
        // apply A on solver dim then B on coder dim
        vector<ll> tmp((S+1)*W,0), nd((S+1)*W,0);
        for(int i=0;i<=S;i++)for(int j=0;j<=C;j++){ ll x=dp[i*W+j]; if(!x)continue; for(int i2=0;i2<=S;i2++) tmp[i2*W+j]=(tmp[i2*W+j]+x*A[i][i2])%MOD; }
        for(int i=0;i<=S;i++)for(int j=0;j<=C;j++){ ll x=tmp[i*W+j]; if(!x)continue; for(int j2=0;j2<=C;j2++) nd[i*W+j2]=(nd[i*W+j2]+x*B[j][j2])%MOD; }
        dp=nd;
    };
    for(int k=0;k<P;k++){
        step(t[k]-cur); cur=t[k];
        for(int i=0;i<=S;i++)for(int j=0;j<=C;j++){
            int ss = g[k]=='B'? i : S-i, cc = g[k]=='B'? j : C-j;
            if(ss<s[k]||cc<c[k]||ss+cc<b[k]) dp[i*W+j]=0;
        }
    }
    step(N-cur);
    cout<<dp[0]%MOD<<endl;
}
