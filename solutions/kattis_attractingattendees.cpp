#include <bits/stdc++.h>
using namespace std;
int main(){int n,m,c;scanf("%d %d %d",&n,&m,&c);vector<vector<int>>fav(m),fans(n+1);
for(int i=0;i<m;i++){int k;scanf("%d",&k);fav[i].resize(k);for(auto&b:fav[i]){scanf("%d",&b);fans[b].push_back(i);}}
vector<int>cnt(n+1,0),have(m);vector<char>in(n+1,1),att(m,1),queued(n+1,0);
for(int i=0;i<m;i++){have[i]=fav[i].size();for(int b:fav[i])cnt[b]++;}
vector<int>q;for(int b=1;b<=n;b++)if(cnt[b]<c){q.push_back(b);queued[b]=1;}
while(!q.empty()){int b=q.back();q.pop_back();in[b]=0;
  for(int i:fans[b]){have[i]--;if(att[i]&&2*have[i]<(int)fav[i].size()){att[i]=0;
    for(int x:fav[i])if(in[x]){cnt[x]--;if(cnt[x]<c&&!queued[x]){queued[x]=1;q.push_back(x);}}}}}
vector<int>r;for(int b=1;b<=n;b++)if(in[b])r.push_back(b);
if(r.empty()){puts("impossible");return 0;}
printf("possible\n%d\n",(int)r.size());for(size_t i=0;i<r.size();i++)printf("%d%c",r[i]," \n"[i+1==r.size()]);}
