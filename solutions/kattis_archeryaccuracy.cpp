#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
// prob of reaching +s before -s starting at x, hit prob p
ld ruin(ld p,int x,int s){ld q=1-p;if(fabsl(p-q)<1e-12L)return (ld)(x+s)/(2*s);
 if(q<p){ld r=q/p;return (1-powl(r,x+s))/(1-powl(r,2*s));}
 ld r=p/q; // rho=1/r >1
 return powl(r,s-x)*(1-powl(r,x+s))/(1-powl(r,2*s));}
int main(){int n;scanf("%d",&n);vector<double>p(n);for(auto&x:p)scanf("%lf",&x);vector<int>s(n);for(auto&x:s)scanf("%d",&x);
 vector<vector<ld>>A(n,vector<ld>(n)),B(n,vector<ld>(n));
 for(int r=0;r<n;r++)for(int j=0;j<n;j++){int prev=r?s[r-1]:0;A[r][j]=ruin(p[j],prev,s[r]);B[r][j]=ruin(p[j],-prev,s[r]);}
 vector<ld>dp(1<<n,0);dp[0]=1;
 for(int m=1;m<(1<<n);m++){int r=__builtin_popcount(m)-1;ld b=0;for(int j=0;j<n;j++)if(m>>j&1){ld v=dp[m^(1<<j)];ld w=v*A[r][j]+(1-v)*B[r][j];if(w>b)b=w;}dp[m]=b;}
 printf("%.9Lf\n",dp[(1<<n)-1]);}
