#include <bits/stdc++.h>
using namespace std;
int main(){int n,k;scanf("%d %d",&n,&k);vector<int> r(n+2,0);r[0]=1%k;long long c=0;
for(int i=0;i<=n;i++){ if(i){for(int j=i;j>=1;j--) r[j]=(r[j]+r[j-1])%k;} for(int j=0;j<=i;j++) if(r[j]==0) c++;}
printf("%lld\n",c);}
