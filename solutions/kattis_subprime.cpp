#include <bits/stdc++.h>
using namespace std;
int main(){ int l,h; string p; cin>>l>>h>>p; const int N=1300000;
    vector<bool> comp(N+1,false); int idx=0,ans=0;
    for(int i=2;i<=N&&idx<h;i++){ if(comp[i]) continue;
        for(long long j=(long long)i*i;j<=N;j+=i) comp[j]=true;
        idx++; if(idx>=l && to_string(i).find(p)!=string::npos) ans++; }
    cout<<ans<<"\n"; }
