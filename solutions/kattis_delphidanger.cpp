#include <bits/stdc++.h>
using namespace std;
int par[200005],sz_[200005];
int fnd(int x){while(par[x]!=x){par[x]=par[par[x]];x=par[x];}return x;}
int main(){int n,m;scanf("%d %d",&n,&m);
 vector<array<int,3>> e(m);
 for(auto&x:e)scanf("%d %d %d",&x[1],&x[2],&x[0]);
 sort(e.begin(),e.end(),[](const array<int,3>&a,const array<int,3>&b){return a[0]>b[0];});
 for(int i=1;i<=n;i++){par[i]=i;sz_[i]=1;}
 vector<vector<int>> adj(n+1); vector<int> col(n+1,-1);
 long long ans=0;
 for(int i=0;i<m;){
   int j=i;while(j<m&&e[j][0]==e[i][0])j++;
   vector<int> vs;
   for(int k=i;k<j;k++){int a=fnd(e[k][1]),b=fnd(e[k][2]);
     if(a==b){puts("impossible");return 0;}
     adj[a].push_back(b);adj[b].push_back(a);vs.push_back(a);vs.push_back(b);}
   for(int s:vs)if(col[s]<0){
     long long c[2]={0,0};col[s]=0;vector<int> st={s};
     while(!st.empty()){int u=st.back();st.pop_back();c[col[u]]+=sz_[u];
       for(int w:adj[u]){if(col[w]<0){col[w]=col[u]^1;st.push_back(w);}
         else if(col[w]==col[u]){puts("impossible");return 0;}}}
     ans+=min(c[0],c[1]);
   }
   for(int s:vs){adj[s].clear();col[s]=-1;}
   for(int k=i;k<j;k++){int a=fnd(e[k][1]),b=fnd(e[k][2]);if(a!=b){if(sz_[a]<sz_[b])swap(a,b);par[b]=a;sz_[a]+=sz_[b];}}
   i=j;
 }
 printf("possible\n%lld\n",ans);
}
