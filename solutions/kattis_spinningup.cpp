#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int k=s.size();vector<int>d(k);for(int i=0;i<k;i++)d[i]=s[k-1-i]-'0';
const int INF=1e9;int dp[2][3],nd[2][3];
for(auto&r:dp)for(int&x:r)x=INF;dp[0][2]=0;
for(int i=0;i<k/2;i++){int j=k-1-i;for(auto&r:nd)for(int&x:r)x=INF;
 for(int cl=0;cl<2;cl++)for(int ch=0;ch<3;ch++){if(dp[cl][ch]>=INF)continue;
  for(int a=0;a<10;a++)for(int b=0;b<10;b++)for(int g=0;g<2;g++){int lo=d[i]+a+cl,hi=d[j]+b+g;
   if(lo%10!=hi%10)continue;if(ch!=2&&hi/10!=ch)continue;
   nd[lo/10][g]=min(nd[lo/10][g],dp[cl][ch]+a+b);}}
 memcpy(dp,nd,sizeof dp);}
int ans=INF;
if(k%2==0){for(int c=0;c<2;c++)ans=min(ans,dp[c][c]);}
else{int m=k/2;for(int cl=0;cl<2;cl++)for(int ch=0;ch<3;ch++){if(dp[cl][ch]>=INF)continue;
 for(int a=0;a<10;a++){int v=d[m]+a+cl;if(ch!=2&&v/10!=ch)continue;ans=min(ans,dp[cl][ch]+a);}}}
printf("%d\n",ans);}
