#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m,w;scanf("%d %d %d",&n,&m,&w);
    vector<vector<pair<int,int>>>g(n+1);
    for(int i=0;i<m;i++){int u,v,t;scanf("%d %d %d",&u,&v,&t);g[u].push_back({v,t});}
    const int NEG=INT_MIN/2;
    vector<int>best(n+1,NEG);vector<char>inq(n+1,0);
    deque<int>q;best[1]=0;q.push_back(1);inq[1]=1;
    while(!q.empty()){int u=q.front();q.pop_front();inq[u]=0;
        for(auto&e:g[u]){int v=e.first;int nv=min(best[u]+e.second,w);
            if(nv>best[v]){best[v]=nv;if(!inq[v]){inq[v]=1;q.push_back(v);}}}
    }
    printf("%d\n",best[n]);
}
