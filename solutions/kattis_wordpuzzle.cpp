#include <bits/stdc++.h>
using namespace std;
int main(){ string p,s; cin>>p>>s; int m=s.size(); const unsigned MOD=1000000007;
    set<string> rots; for(int k=0;k<m;k++) rots.insert(s.substr(k)+s.substr(0,k));
    unsigned long long ans=0;
    for(const string& t:rots){
        vector<int> where[26]; for(int j=m-1;j>=0;j--) where[t[j]-'a'].push_back(j); // descending j
        vector<unsigned> dp(m+1,0); dp[0]=1;
        for(char c:p) for(int j:where[c-'a']){ dp[j+1]+=dp[j]; if(dp[j+1]>=MOD) dp[j+1]-=MOD; }
        ans+=dp[m];
    }
    cout<<ans%MOD<<"\n"; }
