#include <bits/stdc++.h>
using namespace std;

vector<int>p;
int f(int x){while(p[x]!=x){p[x]=p[p[x]];x=p[x];}return x;}
void un(int a,int b){a=f(a);b=f(b);if(a!=b)p[a]=b;}
int main(){int R,C;cin>>R>>C;vector<string>g(R);for(auto&s:g)cin>>s;
// triangles per cell: 0 top,1 right,2 bottom,3 left; node 4*R*C = outside
int O=4*R*C;p.resize(O+1);iota(p.begin(),p.end(),0);
auto id=[&](int r,int c,int k){return 4*(r*C+c)+k;};
for(int r=0;r<R;r++)for(int c=0;c<C;c++){char ch=g[r][c];
if(ch=='/'){un(id(r,c,0),id(r,c,3));un(id(r,c,1),id(r,c,2));}
else if(ch=='\\'){un(id(r,c,0),id(r,c,1));un(id(r,c,2),id(r,c,3));}
else{un(id(r,c,0),id(r,c,1));un(id(r,c,1),id(r,c,2));un(id(r,c,2),id(r,c,3));}
if(r==0)un(id(r,c,0),O);else un(id(r,c,0),id(r-1,c,2));
if(r==R-1)un(id(r,c,2),O);
if(c==0)un(id(r,c,3),O);else un(id(r,c,3),id(r,c-1,1));
if(c==C-1)un(id(r,c,1),O);}
int cnt=0;for(int i=0;i<=O;i++)if(f(i)==i)cnt++;
cout<<cnt-1<<"\n";}
