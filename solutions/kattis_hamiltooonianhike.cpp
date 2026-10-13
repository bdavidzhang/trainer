#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;scanf("%d %d",&n,&m);vector<vector<int>>g(n+1);for(int i=0;i<m;i++){int x,y;scanf("%d %d",&x,&y);g[x].push_back(y);g[y].push_back(x);}
 vector<int>dep(n+1,-1),it(n+1,0),st,out;out.reserve(n);
 st.push_back(1);dep[1]=0;out.push_back(1);
 while(!st.empty()){int v=st.back();
  if(it[v]<(int)g[v].size()){int w=g[v][it[v]++];if(dep[w]<0){dep[w]=dep[v]+1;if(dep[w]%2==0)out.push_back(w);st.push_back(w);}}
  else{if(dep[v]%2==1)out.push_back(v);st.pop_back();}}
 for(int i=0;i<n;i++)printf("%d%c",out[i],i+1<n?' ':'\n');}
