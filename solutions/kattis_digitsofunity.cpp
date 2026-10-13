#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=998244353;
ll pw(ll b,ll e){ll r=1;b%=MOD;while(e){if(e&1)r=r*b%MOD;b=b*b%MOD;e>>=1;}return r;}
int main(){
    int n,k,m;cin>>n>>k>>m;
    int B=0;while((1<<B)<=m)B++;
    if(k>B){puts("0");return 0;}
    int N=1<<B;
    vector<int>f(N,0);
    for(int i=1;i<=m;i++)f[i]=1;
    for(int b=0;b<B;b++)for(int s=0;s<N;s++)if(!(s>>b&1))f[s]+=f[s|1<<b];
    vector<ll>fact(m+1),inv(m+1);
    fact[0]=1;for(int i=1;i<=m;i++)fact[i]=fact[i-1]*i%MOD;
    inv[m]=pw(fact[m],MOD-2);for(int i=m;i>0;i--)inv[i-1]=inv[i]*i%MOD;
    // w[s] = sum_{j=k..s} C(s,j) (-1)^{s-j}
    ll C[32][32]={};for(int i=0;i<32;i++){C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;}
    vector<ll>w(B+1,0);
    for(int s=k;s<=B;s++){ll v=0;for(int j=k;j<=s;j++){if((s-j)&1)v-=C[s][j];else v+=C[s][j];}w[s]=((v%MOD)+MOD)%MOD;}
    ll ans=0;
    for(int s=1;s<N;s++){int pc=__builtin_popcount(s);if(pc<k||f[s]<n)continue;
        ans=(ans+w[pc]*(fact[f[s]]*inv[f[s]-n]%MOD))%MOD;}
    cout<<ans<<"\n";
}
