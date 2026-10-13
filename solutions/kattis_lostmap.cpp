#include <bits/stdc++.h>
using namespace std;
static int D[2500][2500];
static char buf[1<<25];size_t bl=0,bp=0;
int gc(){if(bp==bl){bl=fread(buf,1,sizeof buf,stdin);bp=0;if(!bl)return -1;}return buf[bp++];}
int rd(){int c=gc();while(c!=-1&&(c<'0'||c>'9'))c=gc();int x=0;while(c>='0'&&c<='9'){x=x*10+c-'0';c=gc();}return x;}
int main(){int n=rd();for(int i=0;i<n;i++)for(int j=0;j<n;j++)D[i][j]=rd();
 vector<int> best(n,INT_MAX),par(n,-1);vector<char> in(n,0);best[0]=0;vector<pair<int,int>> res;
 for(int it=0;it<n;it++){int u=-1;for(int i=0;i<n;i++)if(!in[i]&&(u<0||best[i]<best[u]))u=i;
  in[u]=1;if(par[u]>=0)res.push_back({min(u,par[u])+1,max(u,par[u])+1});
  for(int i=0;i<n;i++)if(!in[i]&&D[u][i]<best[i]){best[i]=D[u][i];par[i]=u;}}
 sort(res.begin(),res.end());for(auto&p:res)printf("%d %d\n",p.first,p.second);}
