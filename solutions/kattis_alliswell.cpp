#include <bits/stdc++.h>
using namespace std;
int main(){
    int r,c,p; cin>>r>>c>>p;
    vector<int> h(p); for(auto&x:h)cin>>x;
    vector<vector<int>> w(r,vector<int>(c,-1));
    vector<int> pr(p,-1),pc(p,-1);
    for(int i=0;i<r;i++)for(int j=0;j<c;j++){string s;cin>>s;
        if(isalpha((unsigned char)s[0])){int id=s[0]-'A'; if(id<p){pr[id]=i;pc[id]=j;}}
        else w[i][j]=atoi(s.c_str());}
    if(w[0][0]<0){puts("-1");return 0;}
    auto hear=[&](int i,int j,int k){ if(pr[k]<0) return false; int dr=i-pr[k],dc=j-pc[k]; return dr*dr+dc*dc<=h[k]*h[k]; };
    int S=r*c*(p+1); const long long INF=LLONG_MAX/4;
    vector<long long> dist(S,INF);
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
    auto id=[&](int i,int j,int k){return (i*c+j)*(p+1)+k;};
    dist[id(0,0,0)]=w[0][0]; pq.push({w[0][0],id(0,0,0)});
    int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop(); if(d>dist[u]) continue;
        int k=u%(p+1), cell=u/(p+1), i=cell/c, j=cell%c;
        if(k==p){printf("%lld\n",d);return 0;}
        if(hear(i,j,k)){int v=u+1; if(d<dist[v]){dist[v]=d;pq.push({d,v});}}
        for(int t=0;t<4;t++){int a=i+dx[t],b=j+dy[t]; if(a<0||b<0||a>=r||b>=c||w[a][b]<0) continue;
            int v=id(a,b,k); if(d+w[a][b]<dist[v]){dist[v]=d+w[a][b];pq.push({dist[v],v});}}
    }
    puts("-1");
}
