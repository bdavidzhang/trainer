#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);long long s=0,m=0;while(n--){long long t;scanf("%lld",&t);s+=t;m=min(m,s);}printf("%lld\n",-m);}
