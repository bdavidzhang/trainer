#include <bits/stdc++.h>
using namespace std;
int main(){int R,N,A,B,X;cin>>R>>N>>A>>B>>X;
  int rows=2*R-1;map<pair<int,int>,int> id;vector<pair<int,int>> pos(1);
  int cnt=0;
  for(int r=0;r<rows;r++){int len=r<R?R+r:R+(rows-1-r);int off=max(0,r-(R-1));
    for(int c=0;c<len;c++){++cnt;id[{r,c+off}]=cnt;pos.push_back({r,c+off});}}
  vector<char> wax(cnt+1,0);for(int i=0;i<X;i++){int w;cin>>w;wax[w]=1;}
  vector<int> d(cnt+1,-1);queue<int> q;d[A]=0;q.push(A);
  int dr[]={0,0,1,1,-1,-1},dc[]={1,-1,0,1,0,-1};
  while(!q.empty()){int u=q.front();q.pop();for(int k=0;k<6;k++){auto it=id.find({pos[u].first+dr[k],pos[u].second+dc[k]});if(it==id.end())continue;int v=it->second;if(wax[v]||d[v]>=0)continue;d[v]=d[u]+1;q.push(v);}}
  if(d[B]<0||d[B]>N)puts("No");else printf("%d\n",d[B]);}
