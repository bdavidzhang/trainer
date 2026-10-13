#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<long long>a(n);for(auto&x:a)scanf("%lld",&x);sort(a.begin(),a.end());printf("%lld\n",a[0]+a[1]);}
