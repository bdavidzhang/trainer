#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<int> par(n+1,0); vector<vector<int>> ch(n+1);
    for(int i=2;i<=n;i++){ scanf("%d",&par[i]); ch[par[i]].push_back(i);}
    vector<char> red(n+1,0);
    for(int i=0;i<m;i++){int r; scanf("%d",&r); red[r]=1;}
    vector<int> order; order.reserve(n); order.push_back(1);
    for(int i=0;i<(int)order.size();i++) for(int c:ch[order[i]]) order.push_back(c);
    vector<vector<long long>> dp(n+1);
    for(int i=1;i<=n;i++) dp[i]={1};
    vector<long long> tmp;
    for(int idx=n-1;idx>=0;idx--){
        int v=order[idx];
        // dp[v] currently product of children; add choosing v itself
        if((int)dp[v].size()<=red[v]) dp[v].resize(red[v]+1,0);
        dp[v][red[v]]=(dp[v][red[v]]+1)%MOD;
        if(v==1) break;
        int p=par[v];
        vector<long long>&a=dp[p],&b=dp[v];
        if(b.size()==1){ long long s=b[0]; if(s!=1) for(auto&x:a) x=x*s%MOD; }
        else if(a.size()==1){ long long s=a[0]; if(s!=1) for(auto&x:b) x=x*s%MOD; a.swap(b); }
        else{
            tmp.assign(a.size()+b.size()-1,0);
            for(size_t i=0;i<a.size();i++) if(a[i]) for(size_t j=0;j<b.size();j++) tmp[i+j]=(tmp[i+j]+a[i]*b[j])%MOD;
            a=tmp;
        }
        vector<long long>().swap(b);
    }
    dp[1].resize(m+1,0);
    for(int k=0;k<=m;k++) printf("%lld\n",dp[1][k]);
}
