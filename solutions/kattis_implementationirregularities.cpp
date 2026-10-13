#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<long long>t(n),s(n);for(auto&x:t)scanf("%lld",&x);for(auto&x:s)scanf("%lld",&x);
 vector<pair<long long,long long>>v;for(int i=0;i<n;i++)if(s[i]!=-1)v.push_back({s[i],t[i]});sort(v.begin(),v.end());
 long long sum=0,ans=0;for(auto&p:v){sum+=p.second;ans=max(ans,(sum+p.first-1)/p.first);}printf("%lld\n",ans);}
