#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;scanf("%d %d",&n,&m);vector<int>bx(n),by(n),cx(m),cy(m);
 for(int i=0;i<n;i++)scanf("%d %d",&bx[i],&by[i]);for(int i=0;i<m;i++)scanf("%d %d",&cx[i],&cy[i]);
 int rx,ry;scanf("%d %d",&rx,&ry);
 int C=m+n-1;
 vector<vector<int>>a(n+1,vector<int>(C+1,0));
 for(int i=1;i<=n;i++){int d=abs(bx[i-1]-rx)+abs(by[i-1]-ry);
  for(int j=1;j<=m;j++)a[i][j]=abs(bx[i-1]-cx[j-1])+abs(by[i-1]-cy[j-1])+d;
  for(int j=m+1;j<=C;j++)a[i][j]=2*d;}
 const int INF=INT_MAX/2;
 vector<int>u(n+1),v(C+1),p(C+1),way(C+1);
 for(int i=1;i<=n;i++){p[0]=i;int j0=0;vector<int>minv(C+1,INF);vector<char>used(C+1,0);
  do{used[j0]=1;int i0=p[j0],delta=INF,j1=0;
   for(int j=1;j<=C;j++)if(!used[j]){int cur=a[i0][j]-u[i0]-v[j];if(cur<minv[j]){minv[j]=cur;way[j]=j0;}if(minv[j]<delta){delta=minv[j];j1=j;}}
   for(int j=0;j<=C;j++)if(used[j]){u[p[j]]+=delta;v[j]-=delta;}else minv[j]-=delta;
   j0=j1;}while(p[j0]!=0);
  do{int j1=way[j0];p[j0]=p[j1];j0=j1;}while(j0);}
 printf("%d\n",-v[0]);}
