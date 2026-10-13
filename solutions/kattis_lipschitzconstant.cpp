#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<pair<long long,long double>> a(n);for(auto&p:a){double z;scanf("%lld %lf",&p.first,&z);p.second=z;}
sort(a.begin(),a.end());long double b=0;for(int i=1;i<n;i++)b=max(b,fabsl(a[i].second-a[i-1].second)/(long double)(a[i].first-a[i-1].first));
printf("%.9Lf\n",b);}
