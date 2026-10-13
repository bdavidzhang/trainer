#include <bits/stdc++.h>
using namespace std;
typedef __int128 L;
int main(){long long W,H;int n;scanf("%lld %lld %d",&W,&H,&n);vector<long long>a(n);for(auto&x:a)scanf("%lld",&x);
 L cov=0;L total=0;
 for(int k=n-1;k>=0;k--){L cap=(L)(W>>k)*(L)(H>>k);L u=cap-4*cov;L c=min((L)a[k],u);total+=c;cov=4*cov+c;}
 if(cov!=(L)W*H)puts("-1");else printf("%lld\n",(long long)total);}
