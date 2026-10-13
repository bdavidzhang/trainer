#include <bits/stdc++.h>
using namespace std;
int main(){int n,m,a,b;cin>>n>>m>>a>>b;const int INF=1e9;vector<vector<int>> d(n+1,vector<int>(n+1,INF));
 for(int i=1;i<=n;i++)d[i][i]=0;vector<array<int,3>> e(m);long long tot=0;
 for(auto&x:e){cin>>x[0]>>x[1]>>x[2];d[x[0]][x[1]]=d[x[1]][x[0]]=min(d[x[0]][x[1]],x[2]);tot+=x[2];}
 for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(d[i][k]+d[k][j]<d[i][j])d[i][j]=d[i][k]+d[k][j];
 int D=d[a][b];
 for(auto&x:e){if(d[a][x[0]]+x[2]+d[x[1]][b]==D||d[a][x[1]]+x[2]+d[x[0]][b]==D)tot-=x[2];}
 cout<<tot<<endl;}
