#include <bits/stdc++.h>
using namespace std;
int main(){int n,s,k;cin>>n>>s>>k;vector<int>c(n,0);for(int i=0;i<k;i++){int x;cin>>x;c[(x-1)/s]++;}
int h=*max_element(c.begin(),c.end());
for(int r=h;r>=1;r--){string l(n,'.');for(int i=0;i<n;i++)if(c[i]>=r)l[i]='#';puts(l.c_str());}
puts(string(n,'-').c_str());}
