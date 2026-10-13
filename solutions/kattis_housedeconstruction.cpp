#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=998244353;
int main(){
    ll x; int n,m; scanf("%lld %d %d",&x,&n,&m);
    int N=n+m, K=m-n;
    vector<vector<pair<ll,int>>> g(K);
    ll s=0;
    for(int j=0;j<N;j++){
        ll p; char t; scanf("%lld %c",&p,&t);
        ll e; int ty;
        if(t=='P'){s++;e=s-1;ty=1;} else {s--;e=s;ty=0;}
        ll z=e>=0? e/K : -((-e+K-1)/K);
        ll rep=e-z*K;
        g[rep].push_back({p+z*x,ty});
    }
    ll total=0, ways=1;
    for(int c=0;c<K;c++){
        auto&v=g[c]; sort(v.begin(),v.end());
        int sz=v.size();
        // expect H P H P ... H
        int r=(sz+1)/2;
        ll cost=0;
        for(int j=0;j+1<r;j++) cost+=v[2*j+2].first-v[2*j+1].first;
        ll best=cost, cnt=1;
        for(int kq=0;kq+1<r;kq++){
            cost+= (v[2*kq+1].first-v[2*kq].first) - (v[2*kq+2].first-v[2*kq+1].first);
            if(cost<best){best=cost;cnt=1;} else if(cost==best) cnt++;
        }
        total+=best; ways=ways*(cnt%MOD)%MOD;
    }
    printf("%lld\n%lld\n",total,ways);
}
