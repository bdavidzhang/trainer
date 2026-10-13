#include <bits/stdc++.h>
using namespace std;
int main(){int n,m,q;cin>>n>>m>>q;vector<string>s(n);for(auto&x:s)cin>>x;vector<int>ok(n,1);
while(q--){int a;char c;cin>>a>>c;for(int i=0;i<n;i++)if(s[i][a-1]!=c)ok[i]=0;}
int cnt=0,id=0;for(int i=0;i<n;i++)if(ok[i]){cnt++;id=i+1;}
if(cnt==1)printf("unique\n%d\n",id);else printf("ambiguous\n%d\n",cnt);}
