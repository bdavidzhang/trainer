#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);int lo=0,hi=INT_MAX;for(int i=0;i<n;i++){int a,b;scanf("%d %d",&a,&b);lo=max(lo,a);hi=min(hi,b);}if(lo>hi)puts("bad news");else printf("%d %d\n",hi-lo+1,lo);}
