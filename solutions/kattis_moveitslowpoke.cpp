#include <bits/stdc++.h>
using namespace std;
int n,m,K,d,s,t;int len[101][101];bool cont[101][101][101];
int main(){scanf("%d %d %d %d %d %d",&n,&m,&K,&d,&s,&t);
 vector<vector<int>> adj(n+1);
 for(int i=0;i<m;i++){int a,b,l;scanf("%d %d %d",&a,&b,&l);len[a][b]=len[b][a]=l;adj[a].push_back(b);adj[b].push_back(a);}
 for(int i=0;i<K;i++){int a,b,c;scanf("%d %d %d",&a,&b,&c);cont[a][b][c]=true;}
 // state: directed edge (a->b), run length of current continuous chain (capped d+1)
 int R=d+2;auto id=[&](int a,int b,int r){return ((a*101)+b)*R+r;};
 vector<int> dist((size_t)101*101*R+R,INT_MAX);
 vector<int> minRun(101*101,INT_MAX);
 typedef pair<int,int> pii;priority_queue<pii,vector<pii>,greater<pii>> pq;
 for(int b:adj[s]){int r=min(len[s][b],d+1);int x=id(s,b,r);dist[x]=len[s][b];pq.push({dist[x],x});}
 while(!pq.empty()){auto [D,x]=pq.top();pq.pop();if(D>dist[x])continue;int r=x%R,ab=x/R,a=ab/101,b=ab%101;
  if(b==t){printf("%d\n",D);return 0;}
  if(minRun[ab]<=r)continue;minRun[ab]=r;
  for(int c:adj[b]){if(c==a)continue;int l=len[b][c];int nr;
   if(cont[a][b][c]){if(r+l>d)continue;nr=r+l;}else nr=min(l,d+1);
   int y=id(b,c,nr);if(D+l<dist[y]){dist[y]=D+l;pq.push({D+l,y});}}}
 puts("impossible");}
