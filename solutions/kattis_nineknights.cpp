#include <bits/stdc++.h>
using namespace std;
int main(){string g[5];for(auto&r:g)cin>>r;int c=0;bool ok=true;
int dx[]={1,1,-1,-1,2,2,-2,-2},dy[]={2,-2,2,-2,1,-1,1,-1};
for(int i=0;i<5;i++)for(int j=0;j<5;j++)if(g[i][j]=='k'){c++;for(int d=0;d<8;d++){int x=i+dx[d],y=j+dy[d];if(x>=0&&x<5&&y>=0&&y<5&&g[x][y]=='k')ok=false;}}
puts(ok&&c==9?"valid":"invalid");}
