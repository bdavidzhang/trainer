#include <bits/stdc++.h>
using namespace std;
int main(){int n,k,c;scanf("%d %d %d",&n,&k,&c);vector<int>t(n),s(n),cnt(n+1,0);vector<char>take(n,0);int got=0;
 for(int i=0;i<n;i++)scanf("%d %d",&t[i],&s[i]);
 for(int i=0;i<n&&got<k;i++)if(cnt[s[i]]<c){cnt[s[i]]++;take[i]=1;got++;}
 for(int i=0;i<n&&got<k;i++)if(!take[i]){take[i]=1;got++;}
 for(int i=0;i<n;i++)if(take[i])printf("%d\n",t[i]);}
