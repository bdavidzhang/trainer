#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double INF=1e18;
int n;ll X[505],Y[505],BX[2],BY[2];
static double g[505][505],dd[505][505],h[2][505][505];
static signed char sd[2][505][505];
int main(){scanf("%d",&n);for(int i=0;i<n;i++)scanf("%lld %lld",&X[i],&Y[i]);
 for(int k=0;k<2;k++)scanf("%lld %lld",&BX[k],&BY[k]);
 for(int i=0;i<n;i++)for(int j=0;j<n;j++){dd[i][j]=sqrt((double)((X[i]-X[j])*(X[i]-X[j])+(Y[i]-Y[j])*(Y[i]-Y[j])));
  for(int k=0;k<2;k++){ll c=(X[j]-X[i])*(BY[k]-Y[i])-(Y[j]-Y[i])*(BX[k]-X[i]);sd[k][i][j]=c>0?1:(c<0?-1:0);}}
 // g[i][j]: min fencing for the sub-polygon on the arc i,i+1,...,j (cyclic), including chord (i,j) when it is a diagonal
 for(int i=0;i<n;i++)for(int j=0;j<n;j++){g[i][j]=INF;h[0][i][j]=h[1][i][j]=INF;}
 for(int i=0;i<n;i++)g[i][(i+1)%n]=0;
 for(int L=2;L<=n-2;L++)for(int i=0;i<n;i++){int j=(i+L)%n;
  double best=INF;double hb[2]={INF,INF};
  for(int s=1;s<L;s++){int k=i+s;if(k>=n)k-=n;double v=g[i][k]+g[k][j];if(v>=INF)continue;
   if(v<best)best=v;
   for(int b=0;b<2;b++){signed char q=sd[b][i][k];if(q!=0&&q==sd[b][k][j]&&q==sd[b][j][i]&&v<hb[b])hb[b]=v;}}
  h[0][i][j]=hb[0];h[1][i][j]=hb[1];
  if(sd[0][i][j]==0||sd[1][i][j]==0||best>=INF)g[i][j]=INF;else g[i][j]=best+dd[i][j];}
 double ans=INF;
 for(int a=0;a<n;a++)for(int L1=2;L1<=n-3;L1++){int b=(a+L1)%n;
  double p0=h[0][a][b]+dd[a][b],p1=h[1][a][b]+dd[a][b];
  if(p0>=INF&&p1>=INF)continue;
  for(int L2=2;L1+L2<=n-1;L2++){int c=(b+L2)%n;
   double rest=g[c][a]+dd[b][c];if(rest>=INF)continue;
   double v=min(p0+h[1][b][c],p1+h[0][b][c])+rest;
   if(v<ans)ans=v;}}
 if(ans>=INF/2)puts("IMPOSSIBLE");else printf("%.6f\n",ans);}
