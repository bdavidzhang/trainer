#include <bits/stdc++.h>
using namespace std;
const long long MOD=998244353;
int main(){
    int n,m; cin>>n>>m; vector<string> g(n); for(auto&s:g)cin>>s;
    int S=1; for(int i=0;i<=m;i++)S*=3;
    int pm1=S/9, pm=S/3; // digit m-1 and digit m weights
    vector<long long> dp(S,0),nd(S);
    dp[0]=1; long long total=1;
    const char* L="CIP"; // C=0 I=1 P=2
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        fill(nd.begin(),nd.end(),0);
        if(g[i][j]=='?') total=total*3%MOD;
        for(int s=0;s<S;s++){ if(!dp[s])continue;
            int left=s%3, up=(s/pm1)%3, diag=(s/pm)%3;
            for(int c=0;c<3;c++){
                if(g[i][j]!='?'&&g[i][j]!=L[c])continue;
                if(i>0&&j>0&&c==0&&left==2&&up==0&&diag==1)continue;
                int t=(s*3+c)%S;
                nd[t]=(nd[t]+dp[s])%MOD;
            }
        }
        swap(dp,nd);
    }
    long long bad=0; for(int s=0;s<S;s++)bad=(bad+dp[s])%MOD;
    cout<<((total-bad)%MOD+MOD)%MOD<<endl;
}
