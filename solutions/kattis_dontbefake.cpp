#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;vector<int>d(86402,0);
for(int i=0;i<n;i++){int m;cin>>m;while(m--){int l,r;cin>>l>>r;d[l]++;d[r+1]--;}}
int best=0,cnt=0,cur=0;for(int t=0;t<86400;t++){cur+=d[t];if(cur>best){best=cur;cnt=1;}else if(cur==best)cnt++;}
printf("%d\n%d\n",best,cnt);}
