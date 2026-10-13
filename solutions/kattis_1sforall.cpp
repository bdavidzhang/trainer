#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;scanf("%d",&n);
    vector<int> dp(n+1,INT_MAX/4), rv(n+1);
    dp[1]=1;
    for(int v=2;v<=n;v++){
        int best=INT_MAX/4;
        // addition: dp[a]+dp[v-a]; rv[i]=dp reversed helper not needed, plain loop
        const int* d=dp.data();
        int h=v/2;
        for(int a=1;a<=h;a++){int t=d[a]+d[v-a]; if(t<best)best=t;}
        for(int a=2;(long long)a*a<=v;a++) if(v%a==0) best=min(best,d[a]+d[v/a]);
        // concatenation
        long long p10=10;
        while(p10<=v){
            int hi=v/p10, lo=v%p10;
            if(lo>0 && lo>=p10/10) best=min(best,d[hi]+d[lo]);
            p10*=10;
        }
        dp[v]=best;
    }
    printf("%d\n",dp[n]);
}
