#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;cin>>n>>m;vector<array<int,26>> c(m);for(auto&a:c)a.fill(0);string s;
for(int i=0;i<n;i++){cin>>s;for(int j=0;j<m;j++)c[j][s[j]-'a']++;}
string r;for(int j=0;j<m;j++){int b=0;for(int x=1;x<26;x++)if(c[j][x]>c[j][b])b=x;r+=char('a'+b);}
cout<<r<<"\n";}
