#include <bits/stdc++.h>
using namespace std;
const int MOD=1e9+7;
int main(){int n,m;scanf("%d %d",&n,&m);vector<int>forb(n+2,0),need(n+2,0);bool bad=0;char w[16];
 for(int i=0;i<m;i++){int l,r;scanf("%d %d %15s",&l,&r,w);
  if(w[0]=='s'){forb[l]++;forb[r]--;} // gaps l..r-1
  else{ if(l==r)bad=1; else need[r-1]=max(need[r-1],l);}}
 if(bad){puts("0");return 0;}
 vector<long long>dp(n+1,0);dp[0]=1;long long S=1;int lo=0,f=0;
 for(int g=1;g<=n-1;g++){f+=forb[g];
  if(!f){dp[g]=S;S=(S+dp[g])%MOD;}
  while(lo<need[g]){S=(S-dp[lo]+MOD)%MOD;dp[lo]=0;lo++;}}
 printf("%lld\n",S*2%MOD);}
