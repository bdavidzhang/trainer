#include <bits/stdc++.h>
using namespace std;
int dp[805][805];
int main(){
    int n; scanf("%d",&n);
    vector<int> a; a.push_back(0);
    for(int i=0;i<n;i++){int x;scanf("%d",&x); if(a.back()!=x)a.push_back(x);}
    if(a.back()!=0)a.push_back(0);
    int m=a.size();
    // strange printer on 0,a,0 where 0 (empty) is a colour; the whole-range stroke of 0 is free
    for(int i=m-1;i>=0;i--){
        dp[i][i]=1;
        for(int j=i+1;j<m;j++){
            if(a[i]==a[j]) dp[i][j]=dp[i][j-1];
            else{
                int b=INT_MAX;
                for(int k=i;k<j;k++) b=min(b,dp[i][k]+dp[k+1][j]);
                dp[i][j]=b;
            }
        }
    }
    printf("%d\n",dp[0][m-1]-1);
}
