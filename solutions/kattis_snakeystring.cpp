#include <bits/stdc++.h>
using namespace std;
int main(){int r,c;cin>>r>>c;vector<string>g(r);for(auto&s:g)cin>>s;string o;
for(int j=0;j<c;j++)for(int i=0;i<r;i++)if(g[i][j]!='.')o+=g[i][j];cout<<o<<"\n";}
