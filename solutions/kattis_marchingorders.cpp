#include <bits/stdc++.h>
using namespace std;
int main(){int n;string s;cin>>n>>s;string lst;for(int i=0;i<n;i++)lst+=char('A'+i);
long long m=0,l=1;
for(int i=0;i<n;i++){int k=n-i;int r=lst.find(s[i]);lst.erase(r,1);
 int tries=0;while(m%k!=r&&tries<=k){m+=l;tries++;}
 if(m%k!=r){puts("NO");return 0;}
 l=l/std::gcd(l,(long long)k)*k;}
if(m>=1000000000LL){puts("NO");return 0;}
printf("YES\n%lld\n",m);}
