#include <bits/stdc++.h>
using namespace std;
const int NEG=-1e9;
int K;vector<vector<int>> ch;vector<int> w;vector<char> term;
vector<int> dfs(int v){ // f[j]: best using exactly j chosen endpoints in subtree (j>=1 includes w[v]); f[0]=0
 vector<int> g(K+1,NEG);g[0]=0;
 for(int c:ch[v]){vector<int> f=dfs(c);vector<int> h(K+1,NEG);
  for(int a=0;a<=K;a++)if(g[a]>NEG)for(int b=0;a+b<=K;b++)if(f[b]>NEG)h[a+b]=max(h[a+b],g[a]+f[b]);
  g=h;}
 vector<int> r(K+1,NEG);r[0]=0;
 for(int j=1;j<=K;j++){int best=g[j];if(term[v])best=max(best,g[j-1]);if(best>NEG)r[j]=best+w[v];}
 return r;}
int main(){int n;if(!(cin>>n>>K))return 0;map<string,int> id;ch.push_back({});w.push_back(0);term.push_back(0);
 for(int i=0;i<n;i++){int s;cin>>s;int cur=0;for(int j=0;j<s;j++){string d,nm;int len,ants;cin>>d>>len>>ants>>nm;
   auto it=id.find(nm);int x;if(it==id.end()){x=ch.size();id[nm]=x;ch.push_back({});w.push_back(ants);term.push_back(0);ch[cur].push_back(x);}else{x=it->second;w[x]=max(w[x],ants);}
   cur=x;}
  term[cur]=1;}
 vector<int> r=dfs(0);int b=0;for(int j=0;j<=K;j++)b=max(b,r[j]);cout<<b<<endl;}
