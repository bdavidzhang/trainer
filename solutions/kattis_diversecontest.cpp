#include <bits/stdc++.h>
using namespace std;
int main(){int n,k;cin>>n>>k;map<string,int>mp;
 for(int i=0;i<n;i++){int t;cin>>t;while(t--){string s;cin>>s;mp[s]|=1<<i;}}
 vector<int>tm;for(auto&p:mp)if(__builtin_popcount(p.second)>k/2)tm.push_back(p.second);
 sort(tm.begin(),tm.end());tm.erase(unique(tm.begin(),tm.end()),tm.end());
 long long ans=0;
 for(int m=0;m<(1<<n);m++){if(__builtin_popcount(m)!=k)continue;bool ok=true;
  for(int t:tm)if(2*__builtin_popcount(m&t)>k){ok=false;break;}
  ans+=ok;}
 cout<<ans<<endl;}
