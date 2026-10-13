#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<long long>x(n);for(auto&v:x)scanf("%lld",&v);sort(x.begin(),x.end());long long ans=0;
for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){int c=0;for(int k=j+1;k<n;k++)if(x[k]<x[i]+x[j])c++;ans+=(1LL<<c)-1;}
printf("%lld\n",ans);}
