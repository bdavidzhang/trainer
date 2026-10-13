#include <bits/stdc++.h>
using namespace std;
int main(){int n,k,s;scanf("%d %d %d",&n,&k,&s);vector<int>a(n);for(auto&x:a)scanf("%d",&x);
const int NEG=-1e9;vector<int>dp(s+1,NEG),nd(s+1);dp[0]=0;
for(int c=0;c<k;c++){map<int,int>cnt;for(int i=c;i<n;i+=k)cnt[a[i]]++;
int pm=NEG;for(int t=0;t<=s;t++){pm=max(pm,dp[t]);nd[t]=pm;}
for(auto&p:cnt){int v=p.first,w=p.second;for(int t=v;t<=s;t++)if(dp[t-v]>NEG)nd[t]=max(nd[t],dp[t-v]+w);}
dp=nd;}
printf("%d\n",n-dp[s]);}
