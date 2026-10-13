#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<int> cnt(k,0); ll tot=0;
    for(int i=0;i<n;i++){ll w;scanf("%lld",&w);tot+=w;cnt[w%k]++;}
    ll groups=cnt[0];
    for(int r=1;r<k;r++){
        int o=k-r;
        if(r<o){int m=min(cnt[r],cnt[o]);groups+=m;cnt[r]-=m;cnt[o]-=m;}
        else if(r==o){groups+=cnt[r]/2;cnt[r]%=2;}
    }
    vector<int> res,c;
    for(int r=1;r<k;r++) if(cnt[r]){res.push_back(r);c.push_back(cnt[r]);}
    int m=res.size();
    vector<ll> mul(m+1,1);
    for(int i=0;i<m;i++) mul[i+1]=mul[i]*(c[i]+1);
    ll N=mul[m];
    vector<int> dp(N,0);
    vector<int> d(m,0);
    for(ll s=1;s<N;s++){
        // increment mixed radix digits
        int sum=0;
        ll t=s;
        for(int i=0;i<m;i++){d[i]=t%(c[i]+1);t/=(c[i]+1);sum+=d[i]*res[i];}
        int b=0;
        for(int i=0;i<m;i++) if(d[i]) b=max(b,dp[s-mul[i]]);
        dp[s]=b+(sum%k==0);
    }
    groups+=dp[N-1];
    printf("%lld\n",tot/k-groups);
}
