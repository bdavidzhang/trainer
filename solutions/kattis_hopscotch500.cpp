#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n,k;scanf("%d %d",&n,&k);vector<vector<int>>cells(k+1);for(int i=0;i<n;i++)for(int j=0;j<n;j++){int x;scanf("%d",&x);cells[x].push_back(i*n+j);}
 const ll INF=LLONG_MAX/4;for(int v=1;v<=k;v++)if(cells[v].empty()){puts("-1");return 0;}
 vector<ll>dp(cells[1].size(),0),nd,br(n),bc(n);vector<int>rs,cs;
 for(int v=1;v<k;v++){fill(br.begin(),br.end(),INF);fill(bc.begin(),bc.end(),INF);
  for(size_t i=0;i<cells[v].size();i++){int r=cells[v][i]/n,c=cells[v][i]%n;br[r]=min(br[r],dp[i]);bc[c]=min(bc[c],dp[i]);}
  rs.clear();cs.clear();for(int i=0;i<n;i++){if(br[i]<INF)rs.push_back(i);if(bc[i]<INF)cs.push_back(i);}
  nd.assign(cells[v+1].size(),INF);
  for(size_t i=0;i<cells[v+1].size();i++){int r=cells[v+1][i]/n,c=cells[v+1][i]%n;ll b=INF;
   for(int x:rs){ll d=br[x]+(ll)(x-r)*(x-r);if(d<b)b=d;}
   for(int x:cs){ll d=bc[x]+(ll)(x-c)*(x-c);if(d<b)b=d;}
   nd[i]=b;}
  dp.swap(nd);}
 printf("%lld\n",*min_element(dp.begin(),dp.end()));}
