#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;cin>>n>>m;vector<vector<int>> w(n,vector<int>(n,0));
for(int b=0;b<m;b++){int p;string s;cin>>p>>s;for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)w[s[i]-'A'][s[j]-'A']+=p;}
vector<vector<char>> r(n,vector<char>(n,0));for(int i=0;i<n;i++){r[i][i]=1;for(int j=0;j<n;j++)if(i!=j&&w[i][j]>w[j][i])r[i][j]=1;}
for(int k=0;k<n;k++)for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(r[i][k]&&r[k][j])r[i][j]=1;
for(int i=0;i<n;i++){bool ok=true;for(int j=0;j<n;j++)if(!r[i][j])ok=false;printf("%c: %s\n",'A'+i,ok?"can win":"can't win");}}
