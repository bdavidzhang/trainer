#include <bits/stdc++.h>
using namespace std;
int main(){
    string s; cin>>s; int n=s.size(), h=n/2;
    vector<int> bad(h); for(int i=0;i<h;i++) bad[i]=s[i]!=s[n-1-i];
    const int INF=1e9;
    // dp[e] = min ops, e = copies of the edge entering current node from the previous one
    array<int,3> dp={0,INF,INF};
    auto okNode=[&](int j,int t){ if(t==0) return !bad[j]; if(t==1) return (bool)bad[j]; return true; };
    int ans=INF;
    for(int j=0;j<h;j++){
        array<int,3> nd={INF,INF,INF};
        for(int e=0;e<3;e++){ if(dp[e]>=INF)continue;
            if(j<h-1){
                for(int f=0;f<3;f++) if(okNode(j,e+f)) nd[f]=min(nd[f],dp[e]+f);
            } else {
                for(int sp=0;sp<3;sp++){
                    int t=e+((n&1)?sp:2*sp);
                    if(okNode(j,t)) ans=min(ans,dp[e]+sp);
                }
            }
        }
        dp=nd;
    }
    cout<<ans<<endl;
}
