#include <bits/stdc++.h>
using namespace std;
const int NEG=INT_MIN/2;
int main(){string s;int C;cin>>s>>C;int n=s.size();
 vector<array<int,26>>ch(1);ch[0].fill(-1);vector<int>par(1,-1),cc(1,-1),dep(1,0),price(1,-1);
 auto ins=[&](const string&t,int p){int u=0;for(char c:t){int x=c-'a';if(ch[u][x]<0){ch[u][x]=ch.size();array<int,26>z;z.fill(-1);ch.push_back(z);par.push_back(u);cc.push_back(x);dep.push_back(dep[u]+1);price.push_back(-1);}u=ch[u][x];}price[u]=max(price[u],p);};
 for(int i=0;i<C;i++){string t;int p;cin>>t>>p;if((int)t.size()>n)continue;ins(t,p);reverse(t.begin(),t.end());ins(t,p);}
 int V=ch.size();
 // nodes sorted by depth (BFS order = creation not sorted); build order by depth
 vector<int>ord;for(int v=1;v<V;v++)ord.push_back(v);
 stable_sort(ord.begin(),ord.end(),[&](int a,int b){return dep[a]<dep[b];});
 // relabel
 vector<int>nid(V,0);for(size_t i=0;i<ord.size();i++)nid[ord[i]]=i+1;
 vector<int>P(V),Cc(V),Dp(V),Pr(V);P[0]=0;Cc[0]=-1;Dp[0]=0;Pr[0]=-1;
 for(int v=1;v<V;v++){int w=nid[v];P[w]=nid[par[v]];Cc[w]=cc[v];Dp[w]=dep[v];Pr[w]=price[v];}
 vector<int>cntDep(n+2,0); // number of nodes (ids 1..) with depth<=d -> upper id bound
 for(int d=1;d<=n;d++){int c=0;for(int v=1;v<V;v++)if(Dp[v]<=d)c=v;cntDep[d]=c;}
 // full[i][j] for i<=j, full[i][i-1]=0
 vector<vector<int>>full(n+2,vector<int>(n+2,NEG));
 for(int i=0;i<=n;i++)full[i+1>n+1?n+1:i+1][i]=0; // placeholder, handled explicitly below
 vector<vector<int>>A(n,vector<int>(V)),Bv(n,vector<int>(V));
 for(int i=n-1;i>=0;i--){
  for(int j=i;j<n;j++){int lim=cntDep[j-i+1];int x=s[j]-'a';
   int*a=A[j].data();int*b=Bv[j].data();
   const int*bp=j>i?Bv[j-1].data():nullptr;
   for(int v=1;v<=lim;v++){int val=NEG;
    if(Cc[v]==x){int p=P[v];if(p==0){if(j==i)val=0;}else if(j>i)val=bp[p];}
    a[v]=val;b[v]=val;}
   for(int mm=i;mm<j;mm++){int fv=full[mm+1][j];if(fv<=NEG)continue;int l2=cntDep[mm-i+1];const int*am=A[mm].data();
    for(int v=1;v<=l2;v++){int t=am[v]+fv;if(t>b[v])b[v]=t;}}
   for(int v=1;v<=lim;v++)if(b[v]<0)b[v]=NEG;
   int best=NEG;
   for(int v=1;v<=lim;v++)if(Pr[v]>=0&&b[v]>NEG)best=max(best,b[v]+Pr[v]);
   full[i][j]=best;}}
 vector<long long>ans(n+1,0);
 for(int j=1;j<=n;j++){ans[j]=ans[j-1];for(int i=1;i<=j;i++)if(full[i-1][j-1]>NEG)ans[j]=max(ans[j],ans[i-1]+full[i-1][j-1]);}
 cout<<ans[n]<<endl;}
