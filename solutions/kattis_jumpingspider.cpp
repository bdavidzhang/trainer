#include <bits/stdc++.h>
using namespace std;
int main(){int R,C;cin>>R>>C;vector<pair<int,int>> p;
 for(int i=0;i<R;i++)for(int j=0;j<C;j++){int x;cin>>x;if(x)p.push_back({i,j});}
 int n=p.size();auto near=[&](int a,int b){return abs(p[a].first-p[b].first)+abs(p[a].second-p[b].second)<=3;};
 vector<int> core(n,0),valid(n,0);
 for(int i=0;i<n;i++){int c=0;for(int j=0;j<n;j++)if(j!=i&&near(i,j))c++;core[i]=c>=7;}
 for(int i=0;i<n;i++){valid[i]=core[i];for(int j=0;j<n&&!valid[i];j++)if(core[j]&&near(i,j))valid[i]=1;}
 vector<int> par(n);iota(par.begin(),par.end(),0);
 function<int(int)> f=[&](int x){return par[x]==x?x:par[x]=f(par[x]);};
 for(int i=0;i<n;i++)if(valid[i])for(int j=i+1;j<n;j++)if(valid[j]&&near(i,j))par[f(i)]=f(j);
 int comps=0,bad=0;for(int i=0;i<n;i++){if(!valid[i])bad++;else if(f(i)==i)comps++;}
 if(comps==0)printf("No\n0\n%d\n",bad);else printf("Yes\n%d\n%d\n",comps-1,bad);}
