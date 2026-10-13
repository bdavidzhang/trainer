#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<long long> d(n,0);
    for(int i=0;i<m;i++){int a,b; scanf("%d %d",&a,&b); d[a-1]++; d[b-1]++;}
    sort(d.rbegin(),d.rend());
    vector<long long> f(n+1),inv(n+1); f[0]=1; for(int i=1;i<=n;i++) f[i]=f[i-1]*i%MOD;
    auto pw=[&](long long b,long long e){ long long r=1; while(e){ if(e&1) r=r*b%MOD; b=b*b%MOD; e>>=1;} return r; };
    inv[n]=pw(f[n],MOD-2); for(int i=n;i>0;i--) inv[i-1]=inv[i]*i%MOD;
    auto C=[&](int a,int b){ return f[a]*inv[b]%MOD*inv[a-b]%MOD; };
    // block boundaries of equal degree
    vector<int> lo(n),hi(n);
    for(int i=0;i<n;i++) lo[i]=(i&&d[i]==d[i-1])?lo[i-1]:i;
    for(int i=n-1;i>=0;i--) hi[i]=(i<n-1&&d[i]==d[i+1])?hi[i+1]:i;
    long long D=2LL*m, pre=0, ans=0;
    if(m==0) ans=1; // k=0
    for(int k=1;k<=n;k++){
        pre+=d[k-1];
        if(pre==(long long)k*(k-1)+(D-pre)){
            int c=hi[k-1]-lo[k-1]+1, j=k-lo[k-1];
            ans=(ans+C(c,j))%MOD;
        }
    }
    printf("%lld\n",ans);
}
