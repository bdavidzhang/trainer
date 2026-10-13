#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int>a(n);for(auto&x:a)scanf("%d",&x);sort(a.begin(),a.end());
long long s=0;for(int i=0;i<n;i++)if(i==0||a[i]!=a[i-1]+1)s+=a[i];printf("%lld\n",s);}
