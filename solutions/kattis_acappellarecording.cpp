#include <bits/stdc++.h>
using namespace std;
int main(){int n;long long d;scanf("%d %lld",&n,&d);vector<long long>a(n);for(auto&x:a)scanf("%lld",&x);sort(a.begin(),a.end());int c=0;for(int i=0;i<n;){int j=i;while(j<n&&a[j]-a[i]<=d)j++;c++;i=j;}printf("%d\n",c);}
