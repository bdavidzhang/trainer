#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<int> val(n);
    for(auto&v:val) scanf("%d",&v);
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){int a,b;scanf("%d %d",&a,&b);a--;b--;adj[a].push_back(b);adj[b].push_back(a);}
    const int B=2*n; // all nodes -> 2 costs 2n, so no new value exceeds 2n
    vector<int> pid(max(B,100)+1,-1); vector<int> primes;
    int LIM=max(B,100);
    vector<char> comp(LIM+1,0);
    for(int i=2;i<=LIM;i++){ if(!comp[i]){pid[i]=primes.size();primes.push_back(i);for(int j=2*i;j<=LIM;j+=i)comp[j]=1;} }
    auto fac=[&](int x,bool &sqf){ vector<int> f; sqf=true; for(int k=0;k<(int)primes.size()&&primes[k]*primes[k]<=x;k++){int p=primes[k]; if(x%p==0){f.push_back(k);x/=p; if(x%p==0)sqf=false; while(x%p==0)x/=p;}} if(x>1)f.push_back(pid[x]); return f;};
    vector<int> ccost; vector<vector<int>> cpr;
    for(int v=2;v<=B;v++){ bool sq; auto f=fac(v,sq); if(sq){ccost.push_back(v);cpr.push_back(f);} }
    int C=ccost.size(), NP=primes.size();
    vector<vector<int>> origPr(101);
    for(int v=2;v<=100;v++){bool sq; origPr[v]=fac(v,sq);}
    // order
    vector<int> par(n,-1),order; order.reserve(n);
    { vector<int> st={0}; par[0]=-1; while(!st.empty()){int u=st.back();st.pop_back();order.push_back(u);for(int w:adj[u])if(w!=par[u]){par[w]=u;st.push_back(w);} } }
    const int INF=1e9;
    vector<vector<int>> best(n);
    int ans=INF;
    for(int idx=n-1;idx>=0;idx--){
        int u=order[idx];
        vector<int> ch; for(int w:adj[u]) if(w!=par[u]) ch.push_back(w);
        vector<int> b(NP,INF);
        int mn=INF;
        auto eval=[&](int cost,const vector<int>& pr){
            long long tot=cost;
            for(int c:ch){ const int* bc=best[c].data(); int m=INF; for(int k:pr) if(bc[k]<m)m=bc[k]; tot+=m; if(tot>=INF) return; }
            int tt=(int)tot;
            if(tt<mn)mn=tt;
            for(int k:pr) if(tt<b[k]) b[k]=tt;
        };
        for(int i=0;i<C;i++) eval(ccost[i],cpr[i]);
        if(val[u]>1) eval(0,origPr[val[u]]);
        best[u]=std::move(b);
        for(int c:ch) vector<int>().swap(best[c]);
        if(idx==0) ans=mn;
    }
    printf("%d\n",ans);
}
