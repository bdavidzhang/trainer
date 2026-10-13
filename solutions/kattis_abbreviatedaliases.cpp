#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,l; cin>>n>>l;
    vector<string> s(n); for(auto&x:s)cin>>x;
    sort(s.begin(),s.end());
    vector<int> lcp(n+1,0);
    for(int i=1;i<n;i++){ int c=0; while(c<l&&s[i][c]==s[i-1][c])c++; lcp[i]=c; }
    long long tot=0;
    for(int i=0;i<n;i++) tot+=min(l,max(lcp[i],lcp[i+1])+1);
    cout<<tot<<"\n";
}
