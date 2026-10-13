#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<long long>a(n);for(auto&x:a)scanf("%lld",&x);
 long double best=0;long long s=0;
 for(int i=0;i<n;i++){s+=a[i];best=max(best,(long double)s/(i+1));}
 s=0;for(int i=n-1;i>=0;i--){s+=a[i];best=max(best,(long double)s/(n-i));}
 printf("%.9Lf\n",best);}
