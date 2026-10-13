#include <bits/stdc++.h>
using namespace std;
int main(){int t;scanf("%d",&t);while(t--){unsigned long long n,d;scanf("%llu %llu",&n,&d);
    __int128 p=1;int s=0;while(p<(__int128)n){p*=(__int128)(d+1);s++;}
    printf("%d\n",s);}}
