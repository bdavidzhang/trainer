#include <bits/stdc++.h>
using namespace std;
int main(){int n,k;scanf("%d %d",&n,&k);vector<int>p(n+1,0),need(n+1,0);for(int i=2;i<=n;i++)scanf("%d",&p[i]);
vector<int>res;
for(int v=n;v>=1;v--){ // need[v] = max dist to uncovered node in subtree (>=0 since v itself)
  if(need[v]>=0&&(need[v]==k-1||v==1)){res.push_back(v);need[v]=-1;}
  if(v>1&&need[v]>=0)need[p[v]]=max(need[p[v]],need[v]+1);
}
sort(res.begin(),res.end());printf("%d\n",(int)res.size());for(size_t i=0;i<res.size();i++)printf("%d%c",res[i]," \n"[i+1==res.size()]);}
