#include <bits/stdc++.h>
using namespace std;
int n; vector<int> fw;
void upd(int i,int v){for(i++;i<=n+1;i+=i&-i)fw[i]=max(fw[i],v);}
int qry(int i){int r=0;for(i++;i>0;i-=i&-i)r=max(r,fw[i]);return r;}
int main(){scanf("%d",&n);vector<int>p(n+1);for(int i=1;i<=n;i++){int a;scanf("%d",&a);p[a]=i;}
 fw.assign(n+3,0);
 // starts[x]: (y, type) type 0 = up edge, 1 = flat edge, 2 = final (no end)
 vector<vector<pair<int,int>>> st(n+1); vector<vector<pair<int,int>>> pend(n+2);
 for(int v=1;v<n;v++){
  int x=p[v]-1; if(x>=0&&x<=v-1) st[x].push_back({v-1-x,0});
  x=v+p[v]-n-1; if(x>=0&&x<=v-1) st[x].push_back({v-1-x,1});
 }
 {int x=p[n]-1; st[x].push_back({n-1-x,2});}
 int best=0;
 for(int x=0;x<n;x++){
  for(auto&e:pend[x])upd(e.first,e.second);
  sort(st[x].begin(),st[x].end());
  for(auto&e:st[x]){int y=e.first;int d=1+qry(y);best=max(best,d);
   if(e.second==1)upd(y+1,d); else if(e.second==0)pend[x+1].push_back({y,d});}
 }
 printf("%d\n",n-best);}
