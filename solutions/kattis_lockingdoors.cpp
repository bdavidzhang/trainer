#include <bits/stdc++.h>
using namespace std;
static int rd(){int c=getchar_unlocked();while(c<'0')c=getchar_unlocked();int x=0;while(c>='0'){x=x*10+c-'0';c=getchar_unlocked();}return x;}
int main(){int n=rd(),m=rd();vector<int>ea(m),eb(m),st(n+2,0),adj(m);
for(int i=0;i<m;i++){ea[i]=rd()-1;eb[i]=rd()-1;st[ea[i]+1]++;}
for(int i=0;i<n;i++)st[i+1]+=st[i];
{vector<int>pos(st.begin(),st.begin()+n);for(int i=0;i<m;i++)adj[pos[ea[i]]++]=eb[i];}
vector<int>idx(n,-1),low(n),comp(n,-1),it(n),stk,cs;int T=0,C=0;
for(int s=0;s<n;s++)if(idx[s]<0){cs.push_back(s);idx[s]=low[s]=T++;it[s]=st[s];stk.push_back(s);
 while(!cs.empty()){int v=cs.back();
  if(it[v]<st[v+1]){int w=adj[it[v]++];
   if(idx[w]<0){idx[w]=low[w]=T++;it[w]=st[w];stk.push_back(w);cs.push_back(w);}
   else if(comp[w]<0)low[v]=min(low[v],idx[w]);}
  else{cs.pop_back();if(!cs.empty())low[cs.back()]=min(low[cs.back()],low[v]);
   if(low[v]==idx[v]){while(true){int w=stk.back();stk.pop_back();comp[w]=C;if(w==v)break;}C++;}}}}
vector<char>hasin(C,0);for(int i=0;i<m;i++)if(comp[ea[i]]!=comp[eb[i]])hasin[comp[eb[i]]]=1;
int r=0;for(int c=0;c<C;c++)r+=!hasin[c];printf("%d\n",r);}
