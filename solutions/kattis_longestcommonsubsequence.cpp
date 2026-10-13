#include <bits/stdc++.h>
using namespace std;
int main(){int n,k;scanf("%d %d",&n,&k);vector<unsigned> after(26,(1u<<26)-1);char buf[64];string first;
for(int i=0;i<n;i++){scanf("%s",buf);if(i==0)first=buf;unsigned m=0;for(int j=k-1;j>=0;j--){int c=buf[j]-'A';after[c]&=m;m|=1u<<c;}}
// after[c] = letters that follow c in every string; DP along first string's order
vector<int>dp(26,0);int best=0;
for(int j=k-1;j>=0;j--){int c=first[j]-'A';int b=0;for(int d=0;d<26;d++)if(after[c]>>d&1)b=max(b,dp[d]);dp[c]=b+1;best=max(best,dp[c]);}
printf("%d\n",best);}
