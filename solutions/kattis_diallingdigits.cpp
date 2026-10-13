#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(0);int n,m;cin>>n>>m;
const char*key="22233344455566677778889999";
unordered_map<string,vector<int>> mp;vector<string> w(n);
for(int i=0;i<n;i++){cin>>w[i];string d=w[i];for(auto&c:d)c=key[c-'a'];mp[d].push_back(i);}
while(m--){string p;cin>>p;auto it=mp.find(p);if(it==mp.end()){cout<<"0\n";continue;}
cout<<it->second.size();for(int i:it->second)cout<<' '<<w[i];cout<<"\n";}}
