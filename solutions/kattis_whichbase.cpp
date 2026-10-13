#include <bits/stdc++.h>
using namespace std;
int main(){int P;scanf("%d",&P);while(P--){int K;char s[64];scanf("%d %s",&K,s);
    long long o=0,d=0,h=0;bool ok=true;
    for(int i=0;s[i];i++){int c=s[i]-'0';if(c>7)ok=false;o=o*8+c;d=d*10+c;h=h*16+c;}
    printf("%d %lld %lld %lld\n",K,ok?o:0,d,h);}}
