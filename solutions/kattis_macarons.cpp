#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
const u64 MOD=1000000000ULL;
int S;
typedef vector<vector<u64>> Mat;
Mat mul(const Mat&a,const Mat&b){Mat c(S,vector<u64>(S,0));
 for(int i=0;i<S;i++){u64*ci=c[i].data();int cnt=0;
  for(int k=0;k<S;k++){u64 x=a[i][k];if(!x)continue;const u64*bk=b[k].data();
   for(int j=0;j<S;j++)ci[j]+=x*bk[j];
   if(++cnt==16){cnt=0;for(int j=0;j<S;j++)ci[j]%=MOD;}}
  for(int j=0;j<S;j++)ci[j]%=MOD;}
 return c;}
int main(){int n;unsigned long long m;cin>>n>>m;S=1<<n;
 u64 fib[12];fib[0]=1;fib[1]=1;for(int i=2;i<12;i++)fib[i]=fib[i-1]+fib[i-2];
 Mat T(S,vector<u64>(S,0));
 for(int a=0;a<S;a++){int fr=(S-1)&~a;
  for(int b=fr;;b=(b-1)&fr){int rem=fr&~b;u64 w=1;int run=0;
   for(int i=0;i<=n;i++){if(i<n&&(rem>>i&1))run++;else{w*=fib[run];run=0;}}
   T[a][b]=w%MOD;if(!b)break;}}
 vector<u64>v(S,0);v[0]=1;
 while(m){if(m&1){vector<u64>nv(S,0);for(int i=0;i<S;i++){if(!v[i])continue;for(int j=0;j<S;j++)nv[j]=(nv[j]+v[i]*T[i][j])%MOD;}v=nv;}
  m>>=1;if(m)T=mul(T,T);}
 cout<<v[0]%MOD<<endl;}
