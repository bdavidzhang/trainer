#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<pair<long long,long long>>v(n);for(auto&p:v)scanf("%lld %lld",&p.first,&p.second);
 bool ok=n%2==0;sort(v.begin(),v.end());
 for(int i=0;ok&&i<n/2;i++){if(v[i].first+v[n-1-i].first!=v[0].first+v[n-1].first||v[i].second+v[n-1-i].second!=v[0].second+v[n-1].second)ok=false;}
 puts(ok?"possible":"impossible");}
