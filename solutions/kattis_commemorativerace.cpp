#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;
 auto rd=[&]()->int{int c=getchar_unlocked();while(c<'0')c=getchar_unlocked();int x=0;while(c>='0'){x=x*10+c-'0';c=getchar_unlocked();}return x;};
 n=rd();m=rd();vector<int>eu(m),ev(m),st(n+2,0),deg(n+1,0);for(int i=0;i<m;i++){eu[i]=rd();ev[i]=rd();st[eu[i]+1]++;deg[ev[i]]++;}
 for(int i=1;i<=n+1;i++)st[i]+=st[i-1];vector<int>adj(m),pos(st.begin(),st.end());for(int i=0;i<m;i++)adj[pos[eu[i]]++]=ev[i];
 vector<int>ord;ord.reserve(n);for(int i=1;i<=n;i++)if(!deg[i])ord.push_back(i);
 vector<int>in(n+1,0),out(n+1,0);
 for(size_t h=0;h<ord.size();h++){int u=ord[h];for(int j=st[u];j<st[u+1];j++){int v=adj[j];in[v]=max(in[v],in[u]+1);if(--deg[v]==0)ord.push_back(v);}}
 for(int h=n-1;h>=0;h--){int u=ord[h];for(int j=st[u];j<st[u+1];j++)out[u]=max(out[u],out[adj[j]]+1);}
 int L=0;for(int i=1;i<=n;i++)L=max(L,out[i]);
 vector<int>cnt(L+1,0),who(L+1,0),whov(L+1,0);
 for(int u=1;u<=n;u++)for(int j=st[u];j<st[u+1];j++){int v=adj[j];if(in[u]+1+out[v]==L){cnt[in[u]]++;who[in[u]]=u;whov[in[u]]=v;}}
 int ans=L;
 for(int i=0;i<L;i++)if(cnt[i]==1){int u=who[i],alt=0;for(int j=st[u];j<st[u+1];j++)if(adj[j]!=whov[i])alt=max(alt,1+out[adj[j]]);ans=min(ans,i+alt);}
 printf("%d\n",ans);}
