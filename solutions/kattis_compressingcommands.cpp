#include <bits/stdc++.h>
using namespace std;
static char buf[1000005];
int main(){int n;scanf("%d",&n);
vector<array<int,27>>ch;ch.reserve(1100000);vector<int>cnt,par;vector<char>isdir;
auto nw=[&](int p,char d){array<int,27>a;a.fill(-1);ch.push_back(a);cnt.push_back(0);par.push_back(p);isdir.push_back(d);return (int)ch.size()-1;};
nw(-1,0);long long base=0;
for(int i=0;i<n;i++){scanf("%s",buf);int cur=0;for(char*s=buf;*s;s++){int c=*s=='/'?26:*s-'a';if(c==26)base++;
  if(ch[cur][c]<0){int x=nw(cur,c==26);ch[cur][c]=x;}
  cur=ch[cur][c];cnt[cur]++;}}
int N=ch.size();vector<long long>val(N);long long best=base;val[0]=base;
// node 1 is "/" = root dir (every path starts with '/')
for(int v=1;v<N;v++){val[v]=val[par[v]];if(isdir[v]&&v!=1){val[v]+=(long long)n-2LL*cnt[v];best=min(best,val[v]);}}
printf("%lld\n",best);}
