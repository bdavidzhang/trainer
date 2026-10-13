#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<long long>a(n);for(auto&x:a)scanf("%lld",&x);sort(a.begin(),a.end());
long long s=a[n-1];for(int i=1;i<n;i++)s+=a[i];printf("%lld\n",s);}
