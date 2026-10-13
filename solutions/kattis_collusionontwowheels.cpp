#include <bits/stdc++.h>
using namespace std;
int n,x[1000],y[1000],col[1000];
bool ok(int D){fill(col,col+n,-1);vector<int>st;
 for(int s=0;s<n;s++)if(col[s]<0){col[s]=0;st.push_back(s);
  while(!st.empty()){int u=st.back();st.pop_back();
   for(int v=0;v<n;v++)if(abs(x[u]-x[v])+abs(y[u]-y[v])>D){if(col[v]<0){col[v]=col[u]^1;st.push_back(v);}else if(col[v]==col[u])return false;}}}
 return true;}
int main(){scanf("%d",&n);for(int i=0;i<n;i++)scanf("%d %d",x+i,y+i);
 int lo=0,hi=2000;while(lo<hi){int m=(lo+hi)/2;if(ok(m))hi=m;else lo=m+1;}
 printf("%d\n",lo);}
