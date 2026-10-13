#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;scanf("%d %d",&n,&m);vector<vector<int>>g(n,vector<int>(m));for(auto&r:g)for(auto&x:r)scanf("%d",&x);
 long long best=LLONG_MAX;
 for(int a=0;a<n;a++)for(int b=0;b<m;b++){long long s=0;for(int i=0;i<n;i++)for(int j=0;j<m;j++)s+=(long long)g[i][j]*(abs(i-a)+abs(j-b));best=min(best,s);}
 printf("%lld\n",best);}
