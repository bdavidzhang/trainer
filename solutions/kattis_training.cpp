#include <bits/stdc++.h>
using namespace std;
int main(){int n;long long s;scanf("%d %lld",&n,&s);for(int i=0;i<n;i++){long long l,r;scanf("%lld %lld",&l,&r);if(l<=s&&s<=r)s++;}printf("%lld\n",s);}
