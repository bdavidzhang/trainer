#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
static char buf[1000005];
int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<array<int,26>> tr(1); tr.reserve(1000005);
    vector<int> term(1,-1);
    for(int i=0;i<n;i++){
        scanf("%s",buf); int u=0;
        for(char*p=buf;*p;p++){ int c=*p-'a'; if(!tr[u][c]){ array<int,26> z; z.fill(0); tr[u][c]=tr.size(); tr.push_back(z); term.push_back(-1);} u=tr[u][c]; }
        term[u]=0;
    }
    // assign ranks in lexicographic (dfs) order
    { int rk=0; vector<pair<int,int>> st; st.push_back({0,0});
      while(!st.empty()){
        auto &tp=st.back(); int u=tp.first;
        if(tp.second==0 && term[u]==0) term[u]=++rk;
        if(tp.second==26){ st.pop_back(); continue; }
        int c=tp.second++; if(tr[u][c]) st.push_back({tr[u][c],0});
      } }
    scanf("%s",buf);
    vector<int> seq; { int u=0; for(char*p=buf;*p;p++){ u=tr[u][*p-'a']; if(term[u]>0){ seq.push_back(term[u]); u=0; } } }
    vector<long long> f(n+1),inv(n+1); f[0]=1; for(int i=1;i<=n;i++) f[i]=f[i-1]*i%MOD;
    auto pw=[&](long long b,long long e){ long long r=1; b%=MOD; while(e){ if(e&1) r=r*b%MOD; b=b*b%MOD; e>>=1;} return r; };
    long long ifk=pw(f[n-k],MOD-2);
    vector<int> bit(n+1,0);
    auto upd=[&](int i){ for(;i<=n;i+=i&-i) bit[i]++; };
    auto qry=[&](int i){ int s=0; for(;i>0;i-=i&-i) s+=bit[i]; return s; };
    long long ans=1;
    for(int i=0;i<k;i++){
        int r=seq[i]; long long smaller=(r-1)-qry(r-1);
        ans=(ans+smaller%MOD*f[n-i-1]%MOD*ifk)%MOD;
        upd(r);
    }
    printf("%lld\n",ans);
}
