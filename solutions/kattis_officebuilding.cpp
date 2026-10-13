#include <bits/stdc++.h>
using namespace std;
int main(){int r,c;cin>>r>>c;vector<vector<int>>a(r,vector<int>(c));int tot=0;for(auto&v:a)for(int&x:v){cin>>x;tot+=x;}
 int s,t;cin>>s>>t;vector<string>p(s);for(auto&x:p)cin>>x;int best=INT_MAX;
 for(int rot=0;rot<4;rot++){int h=p.size(),w=p[0].size();
  for(int i=0;i+h<=r;i++)for(int j=0;j+w<=c;j++){int sum=0;for(int x=0;x<h;x++)for(int y=0;y<w;y++)if(p[x][y]=='#')sum+=a[i+x][j+y];best=min(best,sum);}
  vector<string>q(w,string(h,'.'));for(int x=0;x<h;x++)for(int y=0;y<w;y++)q[y][h-1-x]=p[x][y];p=q;}
 cout<<tot-best<<"\n";}
