#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull CAP=2000000000000000000ULL;
int n;vector<vector<int>> adj;vector<ull> tot;
ull addc(ull a,ull b){ull s=a+b;return s>CAP?CAP:s;}
ull mulc(ull a,ull b){unsigned __int128 p=(unsigned __int128)a*b;return p>CAP?CAP:(ull)p;}
int main(){long long K;scanf("%d %lld",&n,&K);adj.resize(n+1);for(int i=0;i<n-1;i++){int u,v;scanf("%d %d",&u,&v);adj[u].push_back(v);adj[v].push_back(u);}
 tot.assign(n+1,0);
 // iterative order
 vector<int> par(n+1,0),ord;ord.reserve(n);vector<int> st={1};par[1]=0;
 while(!st.empty()){int v=st.back();st.pop_back();ord.push_back(v);for(int w:adj[v])if(w!=par[v]){par[w]=v;st.push_back(w);}}
 vector<vector<ull>> dp(n+1);
 for(int i=n-1;i>=0;i--){int v=ord[i];vector<ull> cur={0,1};
  for(int w:adj[v])if(w!=par[v]){vector<ull>&c=dp[w];int a=cur.size()-1,b=c.size()-1;vector<ull> nx(a+b+1,0);
   for(int x=1;x<=a;x++){if(!cur[x])continue;nx[x]=addc(nx[x],cur[x]);for(int y=1;y<=b;y++)if(c[y])nx[x+y]=addc(nx[x+y],mulc(cur[x],c[y]));}
   cur.swap(nx);vector<ull>().swap(c);}
  for(size_t s=1;s<cur.size();s++)tot[s]=addc(tot[s],cur[s]);
  dp[v].swap(cur);}
 ull k=K;for(int s=1;s<=n;s++){if(tot[s]>=k){printf("%d\n",s);return 0;}k-=tot[s];}
 puts("-1");}
