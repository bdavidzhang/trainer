#include <bits/stdc++.h>
using namespace std;
int main(){string a,b;cin>>a>>b;int n=a.size();int l=0,r=n-1;while(a[l]==b[l])l++;while(a[r]==b[r])r--;
  for(int i=l;i<=r;i++)if(a[i]!=b[l+r-i]){puts("0");return 0;}
  long long c=1;l--;r++;while(l>=0&&r<n&&a[l]==a[r]){c++;l--;r++;}
  printf("%lld\n",c);}
