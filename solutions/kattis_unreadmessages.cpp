#include <bits/stdc++.h>
using namespace std;
int main(){long long n;int m;scanf("%lld %d",&n,&m);map<long long,int> last;long long tot=0;
for(int i=1;i<=m;i++){long long s;scanf("%lld",&s);int l=last.count(s)?last[s]:0;tot+=(n-1)-(long long)(i-1-l);last[s]=i;printf("%lld\n",tot);}}
