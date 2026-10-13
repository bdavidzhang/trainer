#include <bits/stdc++.h>
using namespace std;
int main(){int k,n,m;scanf("%d %d %d",&k,&n,&m);vector<array<int,4>> f(m);for(auto&x:f)scanf("%d %d %d %d",&x[0],&x[1],&x[2],&x[3]);
 vector<vector<long long>> arr(n+2,vector<long long>(k+1,0));
 for(int i=0;i<k*n;i++){int a,b,c;scanf("%d %d %d",&a,&b,&c);arr[b][a]+=c;}
 vector<long long> have(k+1,0);
 for(int d=1;d<=n;d++){for(int a=1;a<=k;a++)have[a]+=arr[d][a];
  vector<long long> land(k+1,0);
  for(auto&x:f)if(x[2]==d){have[x[0]]-=x[3];land[x[1]]+=x[3];}
  for(int a=1;a<=k;a++){if(have[a]<0){puts("suboptimal");return 0;}}
  for(int a=1;a<=k;a++)have[a]+=land[a];}
 puts("optimal");}
