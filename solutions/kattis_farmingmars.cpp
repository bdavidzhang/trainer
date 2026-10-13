#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;scanf("%d %d",&n,&m);vector<int>a(n);for(int i=0;i<n;i++){int x,y;scanf("%d.%d",&x,&y);a[i]=x*1000000+y;}
 while(m--){int l,r;scanf("%d %d",&l,&r);l--;r--;int c=0,cnt=0;for(int i=l;i<=r;i++){if(cnt==0){c=a[i];cnt=1;}else if(a[i]==c)cnt++;else cnt--;}
  int k=0;for(int i=l;i<=r;i++)k+=a[i]==c;puts(2*k>r-l+1?"usable":"unusable");}}
