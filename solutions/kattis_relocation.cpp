#include <bits/stdc++.h>
using namespace std;
int main(){int n,q;scanf("%d %d",&n,&q);vector<long long>x(n+1);for(int i=1;i<=n;i++)scanf("%lld",&x[i]);
while(q--){int t;long long a,b;scanf("%d %lld %lld",&t,&a,&b);if(t==1)x[a]=b;else printf("%lld\n",llabs(x[a]-x[b]));}}
