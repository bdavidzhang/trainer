#include <bits/stdc++.h>
using namespace std;
// Region: w-wide full rows plus a partial row, margin 2. Fence: cover every 4-neighbour of the
// region with non-overlapping L-trominoes (free to stick outward) via DFS with backtracking.
int H,W;vector<string>g;vector<pair<int,int>>B;
bool fr(int r,int c){return r>=0&&r<H&&c>=0&&c<W&&g[r][c]=='.';}
bool reg(int r,int c){return r>=0&&r<H&&c>=0&&c<W&&g[r][c]=='R';}
bool tryp(int cr,int cc,int dr,int dc,bool put){
  if(put){if(!fr(cr,cc)||!fr(cr+dr,cc)||!fr(cr,cc+dc))return false;g[cr][cc]='O';g[cr+dr][cc]='#';g[cr][cc+dc]='#';return true;}
  g[cr][cc]='.';g[cr+dr][cc]='.';g[cr][cc+dc]='.';return true;}
bool dfs(size_t i){while(i<B.size()&&g[B[i].first][B[i].second]!='.')i++;if(i==B.size())return true;
  int r=B[i].first,c=B[i].second;
  for(int dr=-1;dr<=1;dr+=2)for(int dc=-1;dc<=1;dc+=2){
    int cs[3][2]={{r,c},{r-dr,c},{r,c-dc}};
    for(auto&q:cs){if(tryp(q[0],q[1],dr,dc,true)){if(dfs(i+1))return true;tryp(q[0],q[1],dr,dc,false);}}}
  return false;}
int main(){int a;scanf("%d",&a);int w=1;while(w*w<a)w++;int full=a/w,rem=a%w;int rows=full+(rem?1:0);
H=rows+4;W=w+4;g.assign(H,string(W,'.'));
for(int i=0;i<a;i++)g[2+i/w][2+i%w]='R';
for(int r=0;r<H;r++)for(int c=0;c<W;c++)if(g[r][c]=='.'&&(reg(r-1,c)||reg(r+1,c)||reg(r,c-1)||reg(r,c+1)))B.push_back({r,c});
bool ok=dfs(0);if(!ok){fprintf(stderr,"FAIL\n");return 1;}
printf("%d %d\n",H,W);for(auto&s:g){for(auto&ch:s)if(ch=='R')ch='.';puts(s.c_str());}}
