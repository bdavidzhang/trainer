#include <bits/stdc++.h>
using namespace std;
int main(){int n,m,S;scanf("%d %d %d",&n,&m,&S);vector<int> c(n*m);for(auto&x:c)scanf("%d",&x);
 const int INF=1e9;vector<int> best(n*m,INF),nw(n*m,INF);
 if(c[0]>S){puts("-1");return 0;}
 best[0]=c[0];if(n*m==1){puts("0");return 0;}
 vector<int> fr={0},fv={c[0]},touched;
 int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
 for(int step=1;!fr.empty();step++){
  touched.clear();
  for(size_t i=0;i<fr.size();i++){int u=fr[i],x=u/m,y=u%m,v0=fv[i];
   for(int d=0;d<4;d++){int a=x+dx[d],b=y+dy[d];if(a<0||b<0||a>=n||b>=m)continue;int v=a*m+b;int w=v0+c[v];
    if(w>S||w>=best[v])continue; if(nw[v]==INF)touched.push_back(v); if(w<nw[v])nw[v]=w;}}
  fr.clear();fv.clear();
  for(int v:touched){ if(nw[v]<best[v]){best[v]=nw[v];fr.push_back(v);fv.push_back(nw[v]);} nw[v]=INF;}
  if(best[n*m-1]<INF){printf("%d\n",step);return 0;}
 }
 puts("-1");}
