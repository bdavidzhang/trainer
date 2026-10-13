#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
int main(){
    int n; scanf("%d",&n);
    vector<int> f(n),deg(n,0); for(auto&v:f){scanf("%d",&v);v--;}
    for(int i=0;i<n;i++) deg[f[i]]++;
    vector<ll> w(n,1); vector<int> st; vector<char> gone(n,0);
    for(int i=0;i<n;i++) if(!deg[i]) st.push_back(i);
    while(!st.empty()){ int v=st.back(); st.pop_back(); gone[v]=1;
        w[f[v]]=w[f[v]]*(1+w[v])%MOD; if(--deg[f[v]]==0) st.push_back(f[v]); }
    ll ans=1;
    for(int i=0;i<n;i++) if(!gone[i]){
        ll p=1; int v=i; while(!gone[v]){ gone[v]=1; p=p*w[v]%MOD; v=f[v]; }
        ans=ans*(1+p)%MOD;
    }
    printf("%lld\n",(ans-1+MOD)%MOD);
}
