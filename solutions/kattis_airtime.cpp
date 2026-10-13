#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<long long>a(n);for(auto&x:a)scanf("%lld",&x);int c=0;for(int i=0;i+2<n;i++)if(a[i+1]-a[i]>a[i+2]-a[i+1])c++;printf("%d\n",c);}
