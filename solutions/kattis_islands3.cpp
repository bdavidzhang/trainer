#include <bits/stdc++.h>
using namespace std;
int r,c;vector<string>g;
void go(int i,int j){if(i<0||j<0||i>=r||j>=c||g[i][j]=='W')return;g[i][j]='W';go(i+1,j);go(i-1,j);go(i,j+1);go(i,j-1);}
int main(){cin>>r>>c;g.resize(r);for(auto&s:g)cin>>s;int a=0;
 for(int i=0;i<r;i++)for(int j=0;j<c;j++)if(g[i][j]=='L'){a++;go(i,j);}
 cout<<a<<endl;}
