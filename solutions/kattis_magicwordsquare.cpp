#include <bits/stdc++.h>
using namespace std;
bool W[26][26][26];int pre[26][26],midm[26][26];
int main(){int n;cin>>n;vector<array<int,3>> ws;
 for(int i=0;i<n;i++){string s;cin>>s;int a=s[0]-'a',b=s[1]-'a',c=s[2]-'a';if(W[a][b][c])continue;W[a][b][c]=1;
  pre[a][b]|=1<<c;midm[a][c]|=1<<b;if(a!=b&&b!=c&&a!=c)ws.push_back({a,b,c});}
 long long ans=0;
 for(auto&r1:ws){int u1=(1<<r1[0])|(1<<r1[1])|(1<<r1[2]);
  for(auto&r2:ws){int u2=(1<<r2[0])|(1<<r2[1])|(1<<r2[2]);if(u1&u2)continue;int u=u1|u2;
   int mx=pre[r1[0]][r2[0]]&pre[r1[2]][r2[1]]&~u; // col0 and anti-diagonal end at bottom-left
   int mz=pre[r1[2]][r2[2]]&pre[r1[0]][r2[1]]&~u; // col2 and main diagonal end at bottom-right
   int my=pre[r1[1]][r2[1]]&~u;
   if(!mx||!mz||!my)continue;
   for(int x=0;x<26;x++)if(mx>>x&1)for(int z=0;z<26;z++)if((mz>>z&1)&&z!=x){
     int m=my&midm[x][z]&~(1<<x)&~(1<<z);ans+=__builtin_popcount(m);}
  }}
 cout<<ans<<endl;}
