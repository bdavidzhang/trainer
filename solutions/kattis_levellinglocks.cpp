#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;scanf("%d",&n);vector<ll> a(n);ll S=0;for(auto&x:a){scanf("%lld",&x);S+=x;}
vector<ll> P(n+1,0);for(int i=0;i<n;i++)P[i+1]=P[i]+a[i]*n-S;
int M=0,m=0;for(int i=0;i<=n;i++){if(P[i]>P[M])M=i;if(P[i]<=P[m])m=i;}
if(M>=m){puts("impossible");return 0;}
// inward from (0,n) to (M,m); state covers chambers i+1..j
int i=0,j=n,ki=0,kj=n;vector<int> rem;
while(true){bool prog=false;
 while(ki<M&&P[ki+1]>=P[j]){ki++;if(P[ki]>=P[i]){for(int k=i+1;k<=ki;k++)rem.push_back(k);i=ki;prog=true;}}
 while(kj>m&&P[kj-1]<=P[i]){kj--;if(P[kj]<=P[j]){for(int k=j;k>kj;k--)rem.push_back(k);j=kj;prog=true;}}
 if(i==M&&j==m)break;
 if(!prog){puts("impossible");return 0;}}
string out;for(int k=m;k>M;k--){out+=to_string(k);out+=' ';}
for(int k=(int)rem.size()-1;k>=0;k--){out+=to_string(rem[k]);out+=' ';}
out.back()='\n';fputs(out.c_str(),stdout);}
