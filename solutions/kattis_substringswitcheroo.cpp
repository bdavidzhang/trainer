#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int main(){mt19937_64 rng(712367);ull rv[26];for(auto&v:rv)v=rng();
int t;cin>>t;while(t--){string a,b;cin>>a>>b;int n=a.size();
vector<ull>pa(n+1,0),pb(n+1,0);for(int i=0;i<n;i++){pa[i+1]=pa[i]+rv[a[i]-'a'];pb[i+1]=pb[i]+rv[b[i]-'a'];}
string ans="NONE";vector<ull>hs;
for(int L=n;L>=1;L--){hs.clear();for(int i=0;i+L<=n;i++)hs.push_back(pb[i+L]-pb[i]);sort(hs.begin(),hs.end());
 bool f=0;for(int i=0;i+L<=n;i++){if(binary_search(hs.begin(),hs.end(),pa[i+L]-pa[i])){ans=a.substr(i,L);f=1;break;}}
 if(f)break;}
cout<<ans<<"\n";}}
