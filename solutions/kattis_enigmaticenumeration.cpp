#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<vector<int>> g;
int main(){
    scanf("%d %d",&n,&m);
    g.assign(n,{});
    for(int i=0;i<m;i++){int u,v;scanf("%d %d",&u,&v);u--;v--;g[u].push_back(v);g[v].push_back(u);}
    vector<int> d(n),par(n),q(n);
    vector<long long> cnt(n);
    int girth=INT_MAX;
    for(int s=0;s<n;s++){
        fill(d.begin(),d.end(),-1);
        int h=0,t=0; q[t++]=s; d[s]=0; par[s]=-1;
        while(h<t){
            int u=q[h++];
            if(2*d[u]+1>=girth) break;
            for(int v:g[u]){
                if(d[v]<0){d[v]=d[u]+1;par[v]=u;q[t++]=v;}
                else if(v!=par[u]) girth=min(girth,d[u]+d[v]+1);
            }
        }
    }
    int k=girth/2;
    long long total=0;
    for(int s=0;s<n;s++){
        fill(d.begin(),d.end(),-1);
        int h=0,t=0; q[t++]=s; d[s]=0; cnt[s]=1;
        while(h<t){
            int u=q[h++];
            if(d[u]>=k) continue;
            for(int v:g[u]){
                if(d[v]<0){d[v]=d[u]+1;cnt[v]=cnt[u];q[t++]=v;}
                else if(d[v]==d[u]+1) cnt[v]+=cnt[u];
            }
        }
        if(girth%2==0){
            for(int i=0;i<t;i++){int v=q[i]; if(d[v]==k) total+=cnt[v]*(cnt[v]-1)/2;}
        } else {
            for(int i=0;i<t;i++){int u=q[i]; if(d[u]==k) for(int v:g[u]) if(v>u&&d[v]==k) total+=cnt[u]*cnt[v];}
        }
    }
    printf("%lld\n",total/girth);
}
