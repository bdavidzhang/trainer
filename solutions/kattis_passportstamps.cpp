#include <bits/stdc++.h>
using namespace std;
int main(){int n;long long p;scanf("%d %lld",&n,&p);__int128 S=0;
 for(int j=0;j<n;j++){long long c;scanf("%lld",&c);
  if((__int128)p-S<=(__int128)(j+1)*(c-1)){printf("%d\n",j);return 0;}
  S+=c;}
 printf("%d\n",n);}
