#include <bits/stdc++.h>
using namespace std;
int fdiv(int a,int b){ int q=a/b; if((a%b!=0)&&((a<0)!=(b<0))) q--; return q; }
int main(){
    int n,l,h; cin>>n>>l>>h;
    vector<int> lo(n+1),hi(n+1);
    for(int i=1;i<=n;i++){
        int a; cin>>a;
        hi[i]=fdiv(h-a,12);
        lo[i]=-fdiv(a-l,12); // ceil((l-a)/12)
    }
    vector<int> dp(n+1,0); dp[0]=INT_MAX;
    for(int i=1;i<=n;i++){
        int mx=INT_MIN,mn=INT_MAX;
        for(int j=i;j>=1;j--){
            mx=max(mx,lo[j]); mn=min(mn,hi[j]);
            if(mx>mn) break;
            if(dp[j-1]>0) dp[i]=max(dp[i],min(dp[j-1],i-j+1));
        }
    }
    cout<<dp[n]<<"\n";
}
