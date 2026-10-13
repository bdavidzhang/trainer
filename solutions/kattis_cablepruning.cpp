#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<vector<pair<int,long long>>> g(n+1);
    vector<int> deg(n+1,0);
    for(int i=0;i<n;i++){int u,v;long long w;scanf("%d %d %lld",&u,&v,&w);g[u].push_back({v,w});g[v].push_back({u,w});deg[u]++;deg[v]++;}
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()^0x9e3779b97f4a7c15ULL);
    vector<ull> h(n+1,0);
    for(int i=0;i<k;i++){int a,b;scanf("%d %d",&a,&b);ull r=rng();h[a]^=r;h[b]^=r;}
    vector<char> rem(n+1,0);
    vector<int> q;
    for(int i=1;i<=n;i++)if(deg[i]==1)q.push_back(i);
    long long ans=0;
    for(size_t qi=0;qi<q.size();qi++){
        int v=q[qi];rem[v]=1;
        for(auto&e:g[v])if(!rem[e.first]){
            if(h[v])ans+=e.second;
            h[e.first]^=h[v];
            if(--deg[e.first]==1)q.push_back(e.first);
        }
    }
    int s=0;for(int i=1;i<=n;i++)if(!rem[i]){s=i;break;}
    // walk the cycle
    unordered_map<ull,long long> grp;
    long long tot=0,best=0;
    int prev=0,cur=s;ull pre=0;
    while(true){
        int nx=0;long long w=0;
        for(auto&e:g[cur])if(!rem[e.first]&&e.first!=prev){nx=e.first;w=e.second;break;}
        pre^=h[cur];
        tot+=w;
        long long &x=grp[pre];x+=w;best=max(best,x);
        prev=cur;cur=nx;
        if(cur==s)break;
    }
    printf("%lld\n",ans+tot-best);
}
