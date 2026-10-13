#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;vector<int>r(n),c(n),id(n);map<string,int>mp;
for(int i=0;i<n;i++){string s;cin>>r[i]>>c[i]>>s;if(!mp.count(s)){int k=mp.size();mp[s]=k;}id[i]=mp[s];}
int m=mp.size();const int INF=1e9;vector<vector<int>>dp(1<<m,vector<int>(n,INF));
for(int i=0;i<n;i++)dp[1<<id[i]][i]=abs(r[i])+abs(c[i]);
for(int mk=1;mk<(1<<m);mk++)for(int i=0;i<n;i++){int d=dp[mk][i];if(d>=INF)continue;
for(int j=0;j<n;j++){if(mk>>id[j]&1)continue;int&x=dp[mk|1<<id[j]][j];x=min(x,d+abs(r[i]-r[j])+abs(c[i]-c[j]));}}
int best=INF;for(int i=0;i<n;i++)if(dp[(1<<m)-1][i]<INF)best=min(best,dp[(1<<m)-1][i]+abs(r[i])+abs(c[i]));
printf("%d\n",best);}
