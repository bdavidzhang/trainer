#include <bits/stdc++.h>
using namespace std;
int n; vector<int> a; vector<pair<int,int>> ops;
void apply(vector<int>&v,int i,int j){ // 0-indexed
 int b[3]={v[i],v[i+1],v[i+2]}; v.erase(v.begin()+i,v.begin()+i+3); v.insert(v.begin()+j,b,b+3);}
void op(int i,int j){apply(a,i,j);ops.push_back({i+1,j+1});}
int main(){scanf("%d",&n);a.resize(n);for(auto&x:a)scanf("%d",&x);
 int m=min(n,8); int pre=n-m;
 for(int t=0;t<pre;t++){int p=find(a.begin(),a.end(),t+1)-a.begin(); if(p==t)continue;
  if(p<=n-3)op(p,t); else {op(p-2,t);op(t+2,t);} }
 // BFS on the last m elements
 vector<int> s(m);for(int i=0;i<m;i++)s[i]=a[pre+i]-pre-1;
 auto enc=[&](const vector<int>&v){int c=0;for(int i=0;i<m;i++)c|=v[i]<<(3*i);return c;};
 auto dec=[&](int c){vector<int>v(m);for(int i=0;i<m;i++)v[i]=(c>>(3*i))&7;return v;};
 vector<int> par(1<<(3*m),-2); vector<short> pm(1<<(3*m),0);
 vector<int> id(m);iota(id.begin(),id.end(),0);int goal=enc(id),st=enc(s);
 queue<int>q;q.push(st);par[st]=-1;
 while(!q.empty()&&par[goal]==-2){int c=q.front();q.pop();vector<int>v=dec(c);
  for(int i=0;i+2<m;i++)for(int j=0;j+2<m;j++)if(i!=j){vector<int>u=v;apply(u,i,j);int e=enc(u);
   if(par[e]==-2){par[e]=c;pm[e]=i*8+j;q.push(e);}}}
 vector<pair<int,int>> tail; for(int c=goal;c!=st;c=par[c])tail.push_back({pm[c]/8,pm[c]%8});
 reverse(tail.begin(),tail.end());
 for(auto&t:tail)op(pre+t.first,pre+t.second);
 printf("%d\n",(int)ops.size());for(auto&o:ops)printf("%d %d\n",o.first,o.second);}
