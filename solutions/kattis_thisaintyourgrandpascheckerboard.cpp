#include <bits/stdc++.h>
using namespace std;

int main(){int n;cin>>n;vector<string>g(n);for(auto&s:g)cin>>s;bool ok=true;
for(int i=0;i<n;i++){int rb=0,cb=0;for(int j=0;j<n;j++){rb+=g[i][j]=='B';cb+=g[j][i]=='B';
if(j+2<n){if(g[i][j]==g[i][j+1]&&g[i][j]==g[i][j+2])ok=false;if(g[j][i]==g[j+1][i]&&g[j][i]==g[j+2][i])ok=false;}}
if(rb*2!=n||cb*2!=n)ok=false;}
cout<<(ok?1:0)<<"\n";}
