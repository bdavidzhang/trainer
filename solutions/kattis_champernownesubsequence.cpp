#include <bits/stdc++.h>
using namespace std;
int main(){int n;static char s[100005];scanf("%d %s",&n,s);int i=0;long long k=0;char b[24];
while(i<n){k++;int l=snprintf(b,sizeof b,"%lld",k);for(int j=0;j<l&&i<n;j++)if(b[j]==s[i])i++;}
printf("%lld\n",k);}
