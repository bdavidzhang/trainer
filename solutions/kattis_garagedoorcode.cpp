#include <bits/stdc++.h>
using namespace std;
static bool sub(const string&c,const string&s){size_t j=0;for(char ch:s){if(j<c.size()&&c[j]==ch)j++;}return j==c.size();}
int main(){int k,n;cin>>k>>n;vector<string>v(n);for(auto&s:v)cin>>s;set<string>res;const string&f=v[0];int m=f.size();
 for(int mask=0;mask<(1<<m);mask++){if(__builtin_popcount(mask)!=k)continue;string c;for(int i=0;i<m;i++)if(mask>>i&1)c+=f[i];
  if(res.count(c))continue;bool ok=true;for(int i=1;i<n&&ok;i++)ok=sub(c,v[i]);if(ok)res.insert(c);}
 printf("%d\n",(int)res.size());for(auto&s:res)puts(s.c_str());}
