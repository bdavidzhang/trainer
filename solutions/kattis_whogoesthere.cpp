#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;cin>>n>>m;vector<int>t(m),r(m,0);for(auto&x:t)cin>>x;
 for(int w=1;w<=100&&n>0;w++){int c=0;for(int i=0;i<m;i++)if(t[i]>=w)c++;
  if(c==0)break;
  if(c<=n){for(int i=0;i<m;i++)if(t[i]>=w)r[i]++;n-=c;}
  else{for(int i=0;i<m&&n>0;i++)if(t[i]>=w){r[i]++;n--;}break;}}
 for(int x:r)printf("%d\n",x);}
