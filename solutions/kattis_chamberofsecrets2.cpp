#include <bits/stdc++.h>
using namespace std;
int main(){int t;scanf("%d",&t);while(t--){int n,m;scanf("%d %d",&n,&m);
 vector<vector<int>>a(n,vector<int>(m));for(auto&r:a)for(int&x:r)scanf("%d",&x);
 int L=n*m/2;vector<int>res;
 if(n%2==0){vector<char>seen(L+1,0);for(int i=0;i<n;i++){if(seen[a[i][0]])continue;seen[a[i][0]]=1;for(int x:a[i])res.push_back(x);}}
 else{int h=m/2;vector<int>byFirst(L+1,-1);for(int i=0;i<n;i++)byFirst[a[i][0]]=i;
  int cur=0;for(int s=0;s<n;s++){for(int j=0;j<h;j++)res.push_back(a[cur][j]);cur=byFirst[a[cur][h]];}}
 for(int i=0;i<(int)res.size();i++)printf("%d%c",res[i],i+1==(int)res.size()?'\n':' ');}}
