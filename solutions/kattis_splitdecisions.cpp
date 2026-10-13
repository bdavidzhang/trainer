#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n; vector<string> w(n); for(auto&s:w)cin>>s;
    sort(w.begin(),w.end()); w.erase(unique(w.begin(),w.end()),w.end()); n=w.size();
    map<array<int,4>,int> cnt; // len,pos,codeA,codeB
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
        if(w[i].size()!=w[j].size())continue;
        int L=w[i].size(),first=-1,last=-1,c=0;
        for(int p=0;p<L;p++)if(w[i][p]!=w[j][p]){ if(first<0)first=p; last=p; c++; }
        if(c==2&&last==first+1){
            int a=(w[i][first]-'A')*26+(w[i][last]-'A'), b=(w[j][first]-'A')*26+(w[j][last]-'A');
            if(a>b)swap(a,b);
            cnt[{L,first,a,b}]++;
        }
    }
    int ans=0; for(auto&kv:cnt)if(kv.second==1)ans++;
    printf("%d\n",ans);
}
