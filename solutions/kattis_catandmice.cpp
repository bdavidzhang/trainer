#include <bits/stdc++.h>
using namespace std;
int n;double X[15],Y[15],S[15],D[15][15],D0[15],pw[16];
static double dp[1<<15][15];
bool ok(double v){
 const double INF=1e18;int F=1<<n;
 for(int m=0;m<F;m++)for(int i=0;i<n;i++)dp[m][i]=INF;
 for(int i=0;i<n;i++){double t=D0[i]/v;if(t<=S[i])dp[1<<i][i]=t;}
 for(int m=1;m<F;m++){int k=__builtin_popcount(m);double sp=v*pw[k];
  for(int i=0;i<n;i++){double c=dp[m][i];if(c>=INF)continue;
   for(int j=0;j<n;j++)if(!(m>>j&1)){double t=c+D[i][j]/sp;if(t<=S[j]&&t<dp[m|1<<j][j])dp[m|1<<j][j]=t;}}}
 for(int i=0;i<n;i++)if(dp[F-1][i]<INF)return true;return false;}
int main(){cin>>n;for(int i=0;i<n;i++)cin>>X[i]>>Y[i]>>S[i];double m;cin>>m;
 pw[0]=1;for(int i=1;i<16;i++)pw[i]=pw[i-1]*m;
 for(int i=0;i<n;i++){D0[i]=hypot(X[i],Y[i]);for(int j=0;j<n;j++)D[i][j]=hypot(X[i]-X[j],Y[i]-Y[j]);}
 double lo=0,hi=1e8;for(int it=0;it<60;it++){double mid=(lo+hi)/2;if(ok(mid))hi=mid;else lo=mid;}
 printf("%.9f\n",hi);
}
