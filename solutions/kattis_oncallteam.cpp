#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;cin>>n>>m;vector<int>f(1<<m,0);
 for(int i=0;i<n;i++){string s;cin>>s;int x=0;for(int j=0;j<m;j++)if(s[j]=='1')x|=1<<j;f[x]++;}
 for(int j=0;j<m;j++)for(int x=0;x<(1<<m);x++)if(x>>j&1)f[x]+=f[x^(1<<j)];
 int full=(1<<m)-1,best=m+1;
 for(int T=1;T<=full;T++){int c=__builtin_popcount(T);if(c<best&&n-f[full^T]<c)best=c;}
 cout<<best-1<<endl;}
