#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u;
int main(){int K,T;cin>>K>>T;vector<int>d(K);int S=0;for(int&v:d){cin>>v;S+=v;}
 static u ways[25][150];ways[0][0]=1;
 for(int c=1;c<=K;c++)for(int s=0;s<150;s++)for(int f=1;f<=6&&f<=s;f++)ways[c][s]+=ways[c-1][s-f];
 static bool sub[25][150];sub[0][0]=true;
 for(int v:d)for(int c=K-1;c>=0;c--)for(int s=149-v;s>=0;s--)if(sub[c][s])sub[c+1][s+v]=true;
 u pw[25];pw[0]=1;for(int i=1;i<=24;i++)pw[i]=pw[i-1]*6;
 u best=0;int bc=0;
 for(int c=0;c<=K;c++)for(int p=0;p<150;p++)if(sub[c][p]){int need=T-S+p;if(need<0||need>=150)continue;
  u val=ways[c][need]*pw[K-c];if(val>best){best=val;bc=c;}}
 cout<<bc<<endl;}
