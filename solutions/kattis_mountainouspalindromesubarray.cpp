#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int>a(n);for(auto&x:a)scanf("%d",&x);int best=-1;
 for(int i=1;i+1<n;i++){if(!(a[i-1]<a[i]&&a[i+1]<a[i]))continue;int k=0;
  while(i-k-1>=0&&i+k+1<n&&a[i-k-1]==a[i+k+1]&&a[i-k-1]<a[i-k])k++;
  if(k>=1)best=max(best,2*k+1);}
 printf("%d\n",best);}
