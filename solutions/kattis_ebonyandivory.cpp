#include <bits/stdc++.h>
using namespace std;
int T[4][6][6][13];
bool blk(int k){int m=k%12;return m==2||m==5||m==7||m==10||m==0;}
int main(){
    int cnt[4],L;
    for(int i=0;i<4;i++)scanf("%d",&cnt[i]);
    scanf("%d",&L);
    memset(T,-1,sizeof T);
    for(int t=0;t<4;t++)for(int e=0;e<cnt[t];e++){
        int a,b;scanf("%d %d",&a,&b);
        for(int h=1;h<=12;h++){int x;scanf("%d",&x);int&r=T[t][a][b][h];if(r<0||x<r)r=x;}
    }
    vector<int> a(L);for(auto&x:a)scanf("%d",&x);
    const long long INF=1e18;
    array<long long,6> dp;dp.fill(0);
    for(int i=1;i<L;i++){
        array<long long,6> nd;nd.fill(INF);
        int p=a[i-1],q=a[i];
        if(p==q){nd=dp;}
        else{
            int lo=min(p,q),hi=max(p,q),t=(blk(lo)?2:0)+(blk(hi)?1:0),h=hi-lo;
            for(int f=1;f<=5;f++)if(dp[f]<INF)for(int g=1;g<=5;g++){
                int fl=p<q?f:g,fu=p<q?g:f;
                int c=T[t][fl][fu][h];
                if(c<0)continue;
                nd[g]=min(nd[g],dp[f]+c);
            }
        }
        dp=nd;
    }
    long long best=INF;for(int f=1;f<=5;f++)best=min(best,dp[f]);
    printf("%lld\n",best);
}
