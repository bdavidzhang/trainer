#include <bits/stdc++.h>
using namespace std;
int main(){int P;scanf("%d",&P);while(P--){int K;unsigned long long N;scanf("%d %llu",&K,&N);
    unsigned long long p=1,q=1;int hb=63-__builtin_clzll(N);
    for(int i=hb-1;i>=0;i--){if(N>>i&1)p+=q;else q+=p;}
    printf("%d %llu/%llu\n",K,p,q);}}
