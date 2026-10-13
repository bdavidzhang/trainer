#include <bits/stdc++.h>
using namespace std;
int main(){
    int P; scanf("%d",&P);
    while(P--){
        int K,m,n; scanf("%d %d %d",&K,&m,&n);
        vector<unsigned long long> dp(n+1,0); dp[0]=1;
        for(long long p=1;p<=n;p*=m)
            for(int i=p;i<=n;i++) dp[i]+=dp[i-p];
        printf("%d %llu\n",K,dp[n]);
    }
}
