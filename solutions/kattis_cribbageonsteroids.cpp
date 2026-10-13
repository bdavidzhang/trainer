#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int main(){int n;cin>>n;const string R="A23456789TJQK";ull cnt[13]={0};ull dp[16]={0};dp[0]=1;
 for(int i=0;i<n;i++){string s;cin>>s;int r=R.find(s[0]);cnt[r]++;int v=min(r+1,10);for(int t=15;t>=v;t--)dp[t]+=dp[t-v];}
 ull ans=2*dp[15];
 for(int r=0;r<13;r++)ans+=cnt[r]*(cnt[r]-1);
 for(int i=0;i<13;){if(!cnt[i]){i++;continue;}int j=i;ull p=1;while(j<13&&cnt[j]){p*=cnt[j];j++;}
  if(j-i>=3)ans+=p*(j-i);i=j;}
 cout<<ans<<endl;}
