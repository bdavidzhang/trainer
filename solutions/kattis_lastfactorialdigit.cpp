#include <bits/stdc++.h>
using namespace std;
int main(){int t;scanf("%d",&t);while(t--){int n;scanf("%d",&n);int f=1;for(int i=1;i<=n;i++)f=f*i%10;printf("%d\n",f);}}
