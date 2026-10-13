#include <bits/stdc++.h>
using namespace std;
int main(){int r,c;cin>>r>>c;vector<string>g(r);for(auto&s:g)cin>>s;int cnt=0,br=0,bc=0;
for(int i=1;i+1<r;i++)for(int j=1;j+1<c;j++){if(g[i][j]!='0')continue;bool ok=true;
for(int a=-1;a<=1;a++)for(int b=-1;b<=1;b++)if((a||b)&&g[i+a][j+b]!='O')ok=false;
if(ok){cnt++;br=i+1;bc=j+1;}}
if(cnt==0)puts("Oh no!");else if(cnt>1)printf("Oh no! %d locations\n",cnt);else printf("%d %d\n",br,bc);}
