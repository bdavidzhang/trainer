#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
int main(){int N;scanf("%d",&N);int H=N*(N+1)/2;vector<double>v(H);for(auto&x:v)scanf("%lf",&x);
 vector<array<double,5>>p(H);for(auto&a:p)for(auto&x:a)scanf("%lf",&x);
 auto id=[&](int r,int c){return r*(r+1)/2+c;};
 vector<array<int,4>>nb(H);
 for(int r=0;r<N;r++)for(int c=0;c<=r;c++){int i=id(r,c);
  nb[i][0]=(r>0&&c>0)?id(r-1,c-1):-1;
  nb[i][1]=(r>0&&c<r)?id(r-1,c):-1;
  nb[i][2]=(r+1<N)?id(r+1,c):-1;
  nb[i][3]=(r+1<N)?id(r+1,c+1):-1;}
 vector<int>idx(H,-1),ord;idx[0]=0;ord.push_back(0);
 for(size_t q=0;q<ord.size();q++){int u=ord[q];for(int k=0;k<4;k++)if(nb[u][k]>=0&&p[u][k]>0&&idx[nb[u][k]]<0){idx[nb[u][k]]=ord.size();ord.push_back(nb[u][k]);}}
 int n=ord.size();vector<vector<ld>>A(n,vector<ld>(n+1,0));
 for(int a=0;a<n;a++){int u=ord[a];A[a][a]+=1;A[a][n]=(ld)p[u][4]*v[u];for(int k=0;k<4;k++)if(nb[u][k]>=0&&p[u][k]>0)A[a][idx[nb[u][k]]]-=p[u][k];}
 for(int c=0;c<n;c++){int pv=c;for(int r=c+1;r<n;r++)if(fabsl(A[r][c])>fabsl(A[pv][c]))pv=r;swap(A[c],A[pv]);
  for(int r=c+1;r<n;r++){if(A[r][c]==0)continue;ld f=A[r][c]/A[c][c];for(int k=c;k<=n;k++)A[r][k]-=f*A[c][k];}}
 vector<ld>x(n);for(int r=n-1;r>=0;r--){ld s=A[r][n];for(int k=r+1;k<n;k++)s-=A[r][k]*x[k];x[r]=s/A[r][r];}
 printf("%.10Lf\n",x[0]);}
