#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static short lcp_[802][802];
static int pref[802];
// counts (X B X at i, later B) configurations: A = XBX, B later, |X|,|B|>=1
ll solveLong(const string&s){
    int n=s.size();
    for(int i=0;i<=n;i++) lcp_[i][n]=lcp_[n][i]=0;
    for(int i=n-1;i>=0;i--) for(int j=n-1;j>=0;j--) lcp_[i][j]= s[i]==s[j]? lcp_[i+1][j+1]+1:0;
    ll res=0;
    for(int p=1;p<n;p++) for(int e=p+1;e<n;e++){
        // B = s[p..e), X = s[p-x..p) == s[e..e+x)
        int mx=min(p,n-e);
        pref[0]=0; bool any=false;
        for(int x=1;x<=mx;x++){ pref[x]=pref[x-1]+(lcp_[p-x][e]>=x); }
        if(pref[mx]==0) continue;
        int b=e-p;
        for(int k=e+1;k+b<=n;k++){
            if(lcp_[p][k]>=b){ int m=min(k-e,mx); res+=pref[m]; }
        }
        (void)any;
    }
    return res;
}
int main(){
    string s; cin>>s; int n=s.size();
    ll ans=solveLong(s);
    string r(s.rbegin(),s.rend());
    ans+=solveLong(r);
    // lcp_ now for r; equal-length count is symmetric under reversal
    for(int i=0;i<n;i++) for(int k=i+1;k<n;k++) ans+=min((int)lcp_[i][k],k-i);
    printf("%lld\n",ans);
}
