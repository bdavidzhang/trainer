#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,m,k; scanf("%d %d %d",&n,&m,&k);
    vector<vector<int>> g(n+1);
    for(int i=0;i<n-1;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);}
    vector<int> P(m); vector<ll> T(m);
    for(int i=0;i<m;i++) scanf("%d %lld",&P[i],&T[i]);
    int e; scanf("%d",&e);
    int c; scanf("%d",&c);
    vector<char> sp(n+1,0);
    for(int i=0;i<c;i++){int x;scanf("%d",&x);sp[x]=1;}
    vector<int> par(n+1,0),dep(n+1,0),top(n+1,0),ord;
    ord.reserve(n); ord.push_back(e);
    for(size_t h=0;h<ord.size();h++){
        int v=ord[h];
        top[v]=sp[v]?v:top[par[v]];
        for(int u:g[v]) if(u!=par[v]){par[u]=v;dep[u]=dep[v]+1;ord.push_back(u);}
    }
    vector<vector<int>> cand(n+1);
    vector<char> dead(m,0);
    for(int i=0;i<m;i++) if(top[P[i]]) cand[top[P[i]]].push_back(i);
    for(int h=n-1;h>=0;h--){
        int v=ord[h];
        if(!sp[v]) continue;
        auto&cv=cand[v];
        auto key=[&](int i){return make_pair((ll)(dep[P[i]]-dep[v])*T[i],T[i]);};
        if((int)cv.size()>k){
            nth_element(cv.begin(),cv.begin()+k,cv.end(),[&](int a,int b){return key(a)<key(b);});
            for(size_t i=k;i<cv.size();i++) dead[cv[i]]=1;
            cv.resize(k);
        }
        int nt=top[par[v]];
        if(nt) for(int i:cv) cand[nt].push_back(i);
        vector<int>().swap(cv);
    }
    for(int i=0;i<m;i++){
        if(dead[i]) puts("-1"); else printf("%lld\n",(ll)dep[P[i]]*T[i]);
    }
}
