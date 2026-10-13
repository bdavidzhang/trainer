#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int F; scanf("%d",&F);
    map<pair<int,int>,int> id; vector<ll> X,Y;
    auto get=[&](int x,int y){ auto it=id.find({x,y}); if(it!=id.end()) return it->second; int k=X.size(); id[{x,y}]=k; X.push_back(x); Y.push_back(y); return k; };
    vector<int> from(2*F), to(2*F);
    for(int i=0;i<F;i++){
        int a,b,c,d; scanf("%d %d %d %d",&a,&b,&c,&d);
        int u=get(a,b), v=get(c,d);
        from[2*i]=u; to[2*i]=v; from[2*i+1]=v; to[2*i+1]=u;
    }
    int V=X.size();
    vector<vector<int>> out(V);
    for(int e=0;e<2*F;e++) out[from[e]].push_back(e);
    vector<int> pos(2*F);
    auto half=[&](ll dx,ll dy){ return (dy>0||(dy==0&&dx>0))?0:1; };
    for(int v=0;v<V;v++){
        sort(out[v].begin(),out[v].end(),[&](int a,int b){
            ll ax=X[to[a]]-X[v], ay=Y[to[a]]-Y[v], bx=X[to[b]]-X[v], by=Y[to[b]]-Y[v];
            int ha=half(ax,ay), hb=half(bx,by);
            if(ha!=hb) return ha<hb;
            return ax*by-ay*bx>0;
        });
        for(int i=0;i<(int)out[v].size();i++) pos[out[v][i]]=i;
    }
    vector<char> used(2*F,0);
    ll total=0, mx=0;
    for(int s=0;s<2*F;s++) if(!used[s]){
        ll area2=0; int e=s;
        while(!used[e]){
            used[e]=1;
            int u=from[e], v=to[e];
            area2+=X[u]*Y[v]-X[v]*Y[u];
            int r=e^1; // v->u
            int k=out[v].size();
            e=out[v][(pos[r]+k-1)%k];
        }
        ll sq=area2*area2;
        total+=sq; mx=max(mx,sq);
    }
    total-=mx;
    printf("%lld.%02d\n", total/4, (int)(total%4)*25);
}
