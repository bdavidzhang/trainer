#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int>a(n);for(auto&x:a)scanf("%d",&x);sort(a.rbegin(),a.rend());long long s=0;for(int i=0;i<n/3;i++)s+=a[2*i+1];printf("%lld\n",s);}
