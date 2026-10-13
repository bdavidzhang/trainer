#include <bits/stdc++.h>
using namespace std;
int n,m;vector<vector<int>> g;
vector<char> bfs(int s){vector<char> v(n+1,0);queue<int>q;q.push(s);v[s]=1;while(!q.empty()){int u=q.front();q.pop();for(int w:g[u])if(!v[w]){v[w]=1;q.push(w);}}return v;}
int main(){scanf("%d %d",&n,&m);g.resize(n+1);for(int i=0;i<m;i++){int x,y;scanf("%d %d",&x,&y);g[x].push_back(y);}int a,b;scanf("%d %d",&a,&b);auto A=bfs(a),B=bfs(b);for(int i=1;i<=n;i++)if(A[i]&&B[i]){printf("yes\n%d\n",i);return 0;}puts("no");}
