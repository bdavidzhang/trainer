#include <bits/stdc++.h>
using namespace std;
int main(){ int n,s; cin>>n>>s; int rem=s,ans=0;
    for(int i=0;i<n;i++){ string o; cin>>o; int need=o[0]-'0'+(o.size()>1?1:0);
        if(rem<need){ans++;rem=s;} rem-=need; }
    cout<<ans<<"\n"; }
