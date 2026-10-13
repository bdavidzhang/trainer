#include <bits/stdc++.h>
using namespace std;
int main(){vector<long long>a;for(int d=1;d<=9;d++){long long x=0;for(int e=d;e<=9;e++){x=x*10+e;a.push_back(x);}}sort(a.begin(),a.end());
int t;scanf("%d",&t);while(t--){long long n;scanf("%lld",&n);auto it=lower_bound(a.begin(),a.end(),n);printf("%lld\n",it==a.end()?-1:*it);}}
