#include <bits/stdc++.h>
using namespace std;
int main(){int t;cin>>t;while(t--){int n;cin>>n;map<string,int>m;while(n--){string s;int c;cin>>s>>c;m[s]+=c;}
vector<pair<int,string>>v;for(auto&p:m)v.push_back({-p.second,p.first});sort(v.begin(),v.end());
cout<<v.size()<<"\n";for(auto&p:v)cout<<p.second<<" "<<-p.first<<"\n";}}
