#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int>c(n+1,0);for(int i=0;i<n;i++){int a;scanf("%d",&a);c[a]++;}
 int r=c[0];for(int x=1;x<=n;x++)r+= c[x]>=x? c[x]-x: c[x];printf("%d\n",r);}
