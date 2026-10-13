#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,p,t; scanf("%d %d %d",&n,&p,&t);
    vector<char> acc(n,0);
    for(int i=0;i<p;i++){int x;scanf("%d",&x);acc[x-1]=1;}
    vector<array<int,52>> d(n); for(auto&a:d)a.fill(-1);
    for(int i=0;i<t;i++){int a,b;char c;scanf("%d %c %d",&a,&c,&b);a--;b--;int k=(c>='a'&&c<='z')?c-'a':26+(c-'A');d[a][k]=b;}
    // lower: 0..25, upper: 26..51
    // states: [0,n): identical so far; n + u*n+v: differ; n+n*n+u*n+v: differ, v may not read lowercase until next uppercase
    int N=n+2*n*n;
    const int INF=1e9;
    vector<int> dist(N,INF);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq;
    auto push=[&](int s,int w){ if(w<dist[s]){dist[s]=w;pq.push({w,s});} };
    push(0,0);
    int ans=-1;
    while(!pq.empty()){
        auto [w,s]=pq.top();pq.pop();
        if(w>dist[s])continue;
        if(s<n){
            int u=s;
            for(int k=0;k<52;k++) if(d[u][k]>=0) push(d[u][k],w+2);
            for(int x=0;x<26;x++) if(d[u][x]>=0){
                push(n+n*n+d[u][x]*n+u,w+1);
                for(int y=0;y<26;y++) if(y!=x&&d[u][y]>=0) push(n+d[u][x]*n+d[u][y],w+2);
            }
        } else if(s<n+n*n){
            int u=(s-n)/n,v=(s-n)%n;
            if(acc[u]&&acc[v]){ans=w;break;}
            for(int x=0;x<26;x++){
                if(d[u][x]>=0) push(n+d[u][x]*n+v,w+1);
                if(d[v][x]>=0) push(n+u*n+d[v][x],w+1);
            }
            for(int x=26;x<52;x++) if(d[u][x]>=0&&d[v][x]>=0) push(n+d[u][x]*n+d[v][x],w+2);
        } else {
            int u=(s-n-n*n)/n,v=(s-n-n*n)%n;
            if(acc[u]&&acc[v]){ans=w;break;}
            for(int x=0;x<26;x++) if(d[u][x]>=0) push(n+n*n+d[u][x]*n+v,w+1);
            for(int x=26;x<52;x++) if(d[u][x]>=0&&d[v][x]>=0) push(n+d[u][x]*n+d[v][x],w+2);
        }
    }
    printf("%d\n",ans);
}
