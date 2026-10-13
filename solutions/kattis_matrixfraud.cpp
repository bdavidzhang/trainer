#include <bits/stdc++.h>
using namespace std;
int main(){
    int r,c; scanf("%d %d",&r,&c);
    vector<string> m(r);
    {static char buf[200005]; for(int i=0;i<r;i++){scanf("%s",buf);m[i]=buf;}}
    if(c>r){ // transpose (the banded property is symmetric)
        vector<string> t(c,string(r,'0'));
        for(int i=0;i<r;i++)for(int j=0;j<c;j++)t[j][i]=m[i][j];
        m.swap(t); swap(r,c);
    }
    // c <= ~447. dp[s][t] for current row, 1-indexed, s<=t
    const int INF=1e9;
    int W=c+2;
    vector<int> dp(W*W,INF),nd(W*W,INF),P(W*W,INF);
    vector<int> A(c+2),B(c+2);
    auto calc=[&](int i){
        // A[s]=sum_{j<s}(one?+1:-1), B[t]=zeros[<=t]+ones[>t]
        int ones=0; for(int j=0;j<c;j++)ones+=m[i][j]=='1';
        A[1]=0; for(int s=2;s<=c;s++)A[s]=A[s-1]+(m[i][s-2]=='1'?1:-1);
        int z=0,o=0;
        for(int t=1;t<=c;t++){ if(m[i][t-1]=='1')o++; else z++; B[t]=z+ones-o; }
    };
    calc(0);
    for(int t=1;t<=c;t++)dp[1*W+t]=A[1]+B[t];
    for(int i=1;i<r;i++){
        calc(i);
        // P[s][t]=min_{s'<=s} dp[s'][t]
        for(int t=1;t<=c;t++){
            int run=INF;
            for(int s=1;s<=c;s++){
                if(s<=t) run=min(run,dp[s*W+t]);
                P[s*W+t]=run;
            }
        }
        for(int s=1;s<=c;s++){
            int run = s>=2 ? P[s*W+s-1] : INF;
            int *pp=&P[s*W], *np=&nd[s*W];
            for(int t=s;t<=c;t++){
                if(pp[t]<run)run=pp[t];
                np[t]= run>=INF?INF:run+A[s]+B[t];
            }
        }
        dp.swap(nd);
    }
    int ans=INF;
    for(int s=1;s<=c;s++)ans=min(ans,dp[s*W+c]);
    printf("%d\n",ans);
}
