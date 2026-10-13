#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int>col(n+1),tot(n+1,0);
 for(int i=1;i<=n;i++){scanf("%d",&col[i]);tot[col[i]]++;}
 vector<vector<pair<int,int>>> adj(n+1);
 for(int i=0;i<n-1;i++){int a,b;scanf("%d %d",&a,&b);adj[a].push_back({b,i});adj[b].push_back({a,i});}
 vector<int> par(n+1,0),pe(n+1,-1),order;order.reserve(n);
 {vector<int> st={1};par[1]=0;while(!st.empty()){int u=st.back();st.pop_back();order.push_back(u);
   for(auto&pr:adj[u])if(pr.first!=par[u]){par[pr.first]=u;pe[pr.first]=pr.second;st.push_back(pr.first);}}}
 vector<unordered_map<int,int>*> mp(n+1,nullptr);vector<long long> S(n+1,0),ans(n-1,0);
 for(int idx=n-1;idx>=0;idx--){int u=order[idx];
  if(!mp[u]){mp[u]=new unordered_map<int,int>();}
  auto add=[&](int v,int c,int k){ // add k nodes of color c to set of v
   int &cnt=(*mp[v])[c];
   S[v]+= (long long)(cnt+k)*(tot[c]-cnt-k)-(long long)cnt*(tot[c]-cnt);cnt+=k;};
  add(u,col[u],1);
  if(pe[u]>=0){ans[pe[u]]=S[u];int p=par[u];
   if(!mp[p]){mp[p]=mp[u];S[p]=S[u];mp[u]=nullptr;}
   else{ if(mp[p]->size()<mp[u]->size()){swap(mp[p],mp[u]);swap(S[p],S[u]);}
    for(auto&kv:*mp[u]){int c=kv.first,k=kv.second;int &cnt=(*mp[p])[c];
     S[p]+=(long long)(cnt+k)*(tot[c]-cnt-k)-(long long)cnt*(tot[c]-cnt);cnt+=k;}
    delete mp[u];mp[u]=nullptr;}
  }}
 for(int i=0;i<n-1;i++)printf("%lld\n",ans[i]);}
