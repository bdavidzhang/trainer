#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;cin>>n;vector<string> s(n);for(auto&x:s)cin>>x;
    string a=s[0];int la=a.size();
    vector<int> best(la,INT_MAX);
    for(int i=0;i<la;i++)best[i]=la-i;
    for(int k=1;k<n;k++){
        const string&t=s[k];int lt=t.size();
        vector<vector<int>> lcp(la+1,vector<int>(lt+1,0));
        for(int i=la-1;i>=0;i--){
            int mx=0;
            for(int j=lt-1;j>=0;j--){
                lcp[i][j]=(a[i]==t[j])?lcp[i+1][j+1]+1:0;
                mx=max(mx,lcp[i][j]);
            }
            best[i]=min(best[i],mx);
        }
    }
    int ans=0;for(int i=0;i<la;i++)ans=max(ans,best[i]);
    cout<<ans<<"\n";
}
