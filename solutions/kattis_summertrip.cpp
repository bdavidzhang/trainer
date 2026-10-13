#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int n=s.size();
 // nxt[c] = next occurrence index of letter c strictly after i
 vector<int>nxt(26,n);long long ans=0;
 for(int i=n-1;i>=0;i--){int c=s[i]-'a';int lim=nxt[c];
  for(int k=0;k<26;k++)if(k!=c&&nxt[k]<lim)ans++;
  nxt[c]=i;}
 printf("%lld\n",ans);}
