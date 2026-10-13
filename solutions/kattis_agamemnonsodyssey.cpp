#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; long long k; scanf("%d %lld",&n,&k);
    vector<vector<pair<int,long long>>> g(n+1); long long sum=0;
    for(int i=0;i<n-1;i++){int u,v;long long c;scanf("%d %d %lld",&u,&v,&c);g[u].push_back({v,c});g[v].push_back({u,c});sum+=c;}
    if(k>=2){printf("%lld\n",sum);return 0;}
    auto far=[&](int s){
        vector<long long> d(n+1,-1); d[s]=0; vector<int> q{s};
        for(size_t i=0;i<q.size();i++){int u=q[i];for(auto&e:g[u]) if(d[e.first]<0){d[e.first]=d[u]+e.second;q.push_back(e.first);}}
        int b=s; for(int i=1;i<=n;i++) if(d[i]>d[b]) b=i;
        return make_pair(b,d[b]);
    };
    auto a=far(1); auto b=far(a.first);
    printf("%lld\n",b.second);
}
