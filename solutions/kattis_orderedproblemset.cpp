#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int>a(n);for(auto&x:a)scanf("%d",&x);bool any=false;
for(int k=2;k<=n;k++){if(n%k)continue;int s=n/k;bool ok=true;for(int i=0;i<n;i++)if((a[i]-1)/s!=i/s)ok=false;if(ok){printf("%d\n",k);any=true;}}
if(!any)puts("-1");}
