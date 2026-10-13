#include <bits/stdc++.h>
using namespace std;
const int M=1e9+7;
int main(){int n;string s;cin>>n>>s;
 vector<int> f(n,0),g(n,0);f[0]=1;long long ans=0;
 for(int j=0;;j++){ // j jumps done so far; next jump moves j+2
  long long mn=(long long)j*(j+3)/2; if(mn>=n)break;
  fill(g.begin(),g.end(),0);
  for(int p=(int)mn;p<n;p++){
   if(s[p]=='#'){f[p]=0;continue;}
   int v=f[p]; if(!v)continue;
   if(p+1>=n)ans+=v; else {f[p+1]+=v;if(f[p+1]>=M)f[p+1]-=M;}
   int q=p+j+2;
   if(q>=n)ans+=v; else {g[q]+=v;if(g[q]>=M)g[q]-=M;}
  }
  ans%=M; swap(f,g);
 }
 printf("%lld\n",ans%M);}
