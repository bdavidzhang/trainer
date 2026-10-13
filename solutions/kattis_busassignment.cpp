#include <bits/stdc++.h>
using namespace std;
int main(){ int n; scanf("%d",&n); long long cur=0,best=0; for(int i=0;i<n;i++){ long long a,b; scanf("%lld %lld",&a,&b); cur-=a; cur+=b; best=max(best,cur);} printf("%lld\n",best); }
