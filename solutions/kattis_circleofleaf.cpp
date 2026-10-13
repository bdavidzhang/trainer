#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=998244353;
int main(){
    int n; scanf("%d",&n);
    vector<vector<int>> ch(n+1);
    for(int i=0;i<n-1;i++){int a,b;scanf("%d %d",&a,&b);ch[a].push_back(b);}
    vector<int> ord; ord.reserve(n); ord.push_back(1);
    for(int i=0;i<(int)ord.size();i++)for(int c:ch[ord[i]])ord.push_back(c);
    vector<ll> f0(n+1),f1(n+1);
    ll ans=1;
    for(int i=n-1;i>=0;i--){
        int v=ord[i];
        if(v==1){
            for(int c:ch[v])ans=ans*((f0[c]+f1[c])%MOD)%MOD;
        } else if(ch[v].empty()){f0[v]=1;f1[v]=1;}
        else{
            ll g0=1,g1=0;
            for(int c:ch[v]){
                ll s=(f0[c]+f1[c])%MOD;
                g1=(g0*f1[c]+g1*s)%MOD;
                g0=g0*s%MOD;
            }
            f0[v]=g0;f1[v]=g1;
        }
    }
    printf("%lld\n",ans);
}
