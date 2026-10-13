#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;scanf("%d %d",&n,&m);vector<vector<int>> g(n);vector<pair<int,int>> es(m);
 for(auto&e:es){scanf("%d %d",&e.first,&e.second);e.first--;e.second--;g[e.first].push_back(e.second);g[e.second].push_back(e.first);}
 auto no=[](){puts("no");exit(0);};
 if(n&(n-1))no();
 int d=0;while((1<<d)<n)d++;
 if((long long)m!=(long long)d*n/2)no();
 for(int i=0;i<n;i++)if((int)g[i].size()!=d)no();
 vector<int> dist(n,-1),lab(n,0),ord;dist[0]=0;ord.push_back(0);
 for(size_t h=0;h<ord.size();h++){int u=ord[h];for(int v:g[u])if(dist[v]<0){dist[v]=dist[u]+1;ord.push_back(v);}}
 if((int)ord.size()!=n)no();
 for(int i=0;i<d;i++)lab[g[0][i]]=1<<i;
 for(int u:ord){if(dist[u]<2)continue;int L=0;for(int v:g[u])if(dist[v]==dist[u]-1)L|=lab[v];lab[u]=L;}
 vector<char> seen(n,0);
 for(int i=0;i<n;i++){if(lab[i]<0||lab[i]>=n||seen[lab[i]])no();seen[lab[i]]=1;}
 for(auto&e:es){int x=lab[e.first]^lab[e.second];if(x==0||(x&(x-1)))no();}
 puts("yes");}
