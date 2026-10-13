#include <bits/stdc++.h>
using namespace std;
int d[403][403];
int main(){int n,b;cin>>n>>b;
 for(int len=1;len<=n;len++)for(int l=1;l+len-1<=n;l++){int r=l+len-1;int best=INT_MAX;
  for(int x=l;x<=r;x++){int c=x+(x>l?d[l][x-1]:0); if(x<r)c=max(c,b+d[x+1][r]); best=min(best,c);}
  d[l][r]=best;}
 printf("%d\n",d[1][n]);}
