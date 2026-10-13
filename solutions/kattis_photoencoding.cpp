#include <bits/stdc++.h>
int main(){int m;scanf("%d",&m);std::vector<int>c(201,0);for(int i=0;i<m;i++){int d;scanf("%d",&d);c[d]++;}
for(int n=1;;n++){bool ok=true;for(int d=0;d<=200&&ok;d++){int cap=d<=n-1?d+1:std::max(0,2*n-1-d);if(c[d]>cap)ok=false;}
if(ok){printf("%d\n",n);return 0;}}}
