#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;vector<string>g(n);for(auto&s:g)cin>>s;
 int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
 vector<vector<int>> lit(n,vector<int>(n,0));
 bool ok=true;
 for(int i=0;i<n;i++)for(int j=0;j<n;j++){
  char c=g[i][j];
  if(c=='?'){lit[i][j]=1;
   for(int d=0;d<4;d++){int x=i+dx[d],y=j+dy[d];
    while(x>=0&&y>=0&&x<n&&y<n&&(g[x][y]=='.'||g[x][y]=='?')){if(g[x][y]=='?')ok=false;lit[x][y]=1;x+=dx[d];y+=dy[d];}}
  } else if(c>='0'&&c<='4'){int k=0;
   for(int d=0;d<4;d++){int x=i+dx[d],y=j+dy[d];if(x>=0&&y>=0&&x<n&&y<n&&g[x][y]=='?')k++;}
   if(k!=c-'0')ok=false;}
 }
 for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(g[i][j]=='.'&&!lit[i][j])ok=false;
 cout<<(ok?1:0)<<endl;}
