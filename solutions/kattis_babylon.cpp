#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=998244353;
int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n; scanf("%d",&n);
        vector<pair<ll,ll>> v(n);
        for(auto&p:v){ll a,b;scanf("%lld %lld",&a,&b); if(a>b)swap(a,b); p={a,b};}
        sort(v.begin(),v.end(),greater<pair<ll,ll>>());
        ll mult=1; int run=0;
        for(int i=0;i<n;i++){
            if(i>0&&v[i]==v[i-1])run++; else run=1;
            mult=mult*run%MOD;
        }
        ll dp[2]; dp[0]=1; dp[1]=(v[0].first!=v[0].second);
        for(int i=1;i<n;i++){
            ll nd[2]={0,0};
            ll A=v[i-1].first,B=v[i-1].second,a=v[i].first,b=v[i].second;
            for(int o=0;o<2;o++){
                if(dp[o]==0)continue;
                ll W=o?B:A,H=o?A:B;
                for(int p=0;p<2;p++){
                    if(p==1&&a==b)continue;
                    ll w=p?b:a,h=p?a:b;
                    if(w<=W&&h<=H){
                        ll ways=((W-w+1)%MOD)*((H-h+1)%MOD)%MOD;
                        nd[p]=(nd[p]+dp[o]*ways)%MOD;
                    }
                }
            }
            dp[0]=nd[0];dp[1]=nd[1];
        }
        printf("%lld\n",(dp[0]+dp[1])%MOD*mult%MOD);
    }
}
