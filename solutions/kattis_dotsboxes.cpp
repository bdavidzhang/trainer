#include <bits/stdc++.h>
using namespace std;
int B;vector<vector<int>>adj;vector<int>mt;vector<int>vis;int stamp=0;
bool dfs(int u){for(int v:adj[u]){if(vis[v]==stamp)continue;vis[v]=stamp;if(mt[v]<0||dfs(mt[v])){mt[v]=u;return true;}}return false;}
int main(){int N;scanf("%d",&N);vector<string>g(2*N-1);for(auto&s:g){static char b[400];scanf("%s",b);s=b;}
 int S=N-1;B=S*S;adj.assign(B,{});int missing=0;
 for(int r=0;r<2*N-1;r++)for(int c=0;c<2*N-1;c++){if((r+c)%2==0)continue;if(g[r][c]!='.')continue;missing++;
  if(r%2==0){ // horizontal edge between dot row r/2, boxes above (r/2-1) and below (r/2), col c/2
   int i=r/2,j=c/2;if(i>=1&&i<S){int a=(i-1)*S+j,b=i*S+j;if(((i-1+j)&1)==0)adj[a].push_back(b);else adj[b].push_back(a);}
  }else{int i=r/2,j=c/2;if(j>=1&&j<S){int a=i*S+j-1,b=i*S+j;if(((i+j-1)&1)==0)adj[a].push_back(b);else adj[b].push_back(a);}}
 }
 mt.assign(B,-1);vis.assign(B,0);int M=0;
 for(int u=0;u<B;u++)if(!adj[u].empty()){stamp++;if(dfs(u))M++;}
 printf("%d\n",missing-(B-M)+1);}
