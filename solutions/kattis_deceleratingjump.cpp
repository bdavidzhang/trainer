#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<long long>p(n+1);for(int i=1;i<=n;i++)scanf("%lld",&p[i]);
 const long long NEG=LLONG_MIN/4;
 // g[i]: best score from square i to n (inclusive) with all jumps <= d
 vector<long long>g(n+1,NEG);g[n]=p[n];
 for(int d=1;d<n;d++)for(int i=n-d;i>=1;i--)if(g[i+d]>NEG)g[i]=max(g[i],p[i]+g[i+d]);
 printf("%lld\n",g[1]);}
