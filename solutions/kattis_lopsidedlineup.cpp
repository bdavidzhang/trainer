#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<long long>d(n,0);for(int i=0;i<n;i++)for(int j=0;j<n;j++){int c;scanf("%d",&c);d[i]+=c;}
 sort(d.begin(),d.end());long long r=0;for(int i=0;i<n;i++)r+=(i<n/2?-d[i]:d[i]);printf("%lld\n",r/2);}
