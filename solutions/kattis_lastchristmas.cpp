#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n;
    map<string,array<int,11>> m;
    for(int i=0;i<n;i++) for(int j=1;j<=10;j++){ string s; cin>>s; auto &v=m[s]; v[0]++; v[j]++; }
    array<int,11> best{}; string who; int cnt=0;
    for(auto &kv:m){
        if(kv.second>best){ best=kv.second; who=kv.first; cnt=1; }
        else if(kv.second==best) cnt++;
    }
    if(cnt==1) cout<<who<<"\n"; else cout<<"tie\n";
}
