#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;long long c[9][9]={};for(size_t i=0;i+1<s.size();i++){int a=s[i]-'1',b=s[i+1]-'1';c[a][b]++;c[b][a]++;}
 int f=s[0]-'1';const int F=1<<9;vector<long long> cut(F,0),dp(F,LLONG_MAX);
 for(int m=1;m<F-1;m++){long long v=0;for(int a=0;a<9;a++)if(m>>a&1)for(int b=0;b<9;b++)if(!(m>>b&1))v+=c[a][b];if(!(m>>f&1))v++;cut[m]=v;}
 dp[0]=0;for(int m=0;m<F;m++){if(dp[m]==LLONG_MAX)continue;for(int a=0;a<9;a++)if(!(m>>a&1)){int nm=m|1<<a;dp[nm]=min(dp[nm],dp[m]+cut[nm]);}}
 printf("%lld\n",dp[F-1]+(long long)s.size());}
