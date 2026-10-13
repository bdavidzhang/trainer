#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n; vector<pair<int,int>> adj[200005];
ll p[200005], ans[200005], dist_[200005];
int par[200005], sz[200005]; bool rem[200005];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){scanf("%lld",&p[i]);ans[i]=p[i]*p[i];}
    for(int i=0;i<n-1;i++){int a,b,w;scanf("%d %d %d",&a,&b,&w);adj[a].push_back({b,w});adj[b].push_back({a,w});}
    vector<int> stk{1}, ord;
    vector<ll> hm,hb;
    while(!stk.empty()){
        int r=stk.back();stk.pop_back();
        ord.clear();ord.push_back(r);par[r]=0;
        for(size_t i=0;i<ord.size();i++){int u=ord[i];sz[u]=1;for(auto&e:adj[u])if(!rem[e.first]&&e.first!=par[u]){par[e.first]=u;ord.push_back(e.first);}}
        for(int i=(int)ord.size()-1;i>0;i--)sz[par[ord[i]]]+=sz[ord[i]];
        int tot=ord.size(),c=r;
        while(true){bool mv=false;for(auto&e:adj[c])if(!rem[e.first]&&e.first!=par[c]&&sz[e.first]*2>tot){c=e.first;mv=true;break;}if(!mv)break;}
        ord.clear();ord.push_back(c);par[c]=0;dist_[c]=0;
        for(size_t i=0;i<ord.size();i++){int u=ord[i];for(auto&e:adj[u])if(!rem[e.first]&&e.first!=par[u]){par[e.first]=u;dist_[e.first]=dist_[u]+e.second;ord.push_back(e.first);}}
        sort(ord.begin(),ord.end(),[&](int a,int b){return p[a]!=p[b]?p[a]>p[b]:dist_[a]<dist_[b];});
        hm.clear();hb.clear();
        for(int u:ord){
            ll m=p[u],b=dist_[u];
            if(!hm.empty()&&hm.back()==m)continue;
            while(hm.size()>=2){
                size_t k=hm.size();
                ll m1=hm[k-2],b1=hb[k-2],m2=hm[k-1],b2=hb[k-1];
                if((b-b1)*(m1-m2)<=(b2-b1)*(m1-m))hm.pop_back(),hb.pop_back();else break;
            }
            hm.push_back(m);hb.push_back(b);
        }
        size_t ptr=0;
        for(int i=(int)ord.size()-1;i>=0;i--){
            int u=ord[i];ll x=p[u];
            while(ptr+1<hm.size()&&hm[ptr+1]*x+hb[ptr+1]<=hm[ptr]*x+hb[ptr])ptr++;
            ans[u]=min(ans[u],hm[ptr]*x+hb[ptr]+dist_[u]);
        }
        rem[c]=true;
        for(auto&e:adj[c])if(!rem[e.first])stk.push_back(e.first);
    }
    ll s=0;for(int i=1;i<=n;i++)s+=ans[i];
    printf("%lld\n",s);
}
