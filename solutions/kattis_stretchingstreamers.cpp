#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
int n; ll x[305]; bool ok[305][305]; ll f[305][305],g[305][305];
int main(){
    scanf("%d",&n); for(int i=0;i<n;i++) scanf("%lld",&x[i]);
    for(int i=0;i<n;i++)for(int j=0;j<n;j++) ok[i][j]= i!=j && std::gcd(x[i],x[j])>1;
    for(int i=0;i<n;i++) g[i][i]=1;
    for(int len=1;len<n;len++) for(int i=0;i+len<n;i++){
        int j=i+len;
        if(ok[i][j]){
            ll s=0; for(int k=i;k<j;k++) s=(s+g[i][k]*g[k+1][j])%MOD;
            f[i][j]=s;
        }
        ll s=0; for(int k=i+1;k<=j;k++) if(f[i][k]) s=(s+f[i][k]*g[k][j])%MOD;
        g[i][j]=s;
    }
    printf("%lld\n",g[0][n-1]);
}
