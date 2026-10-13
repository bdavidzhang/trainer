#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int main(){
    int n; scanf("%d",&n); vector<int> w(n); int S=0; for(auto&x:w){scanf("%d",&x); S+=x;}
    const ull M[2]={998244353ULL,1000000007ULL};
    vector<unsigned> c[2];
    for(int t=0;t<2;t++){ c[t].assign(S+1,0); c[t][0]=1;
        for(int x:w) for(int s=S;s>=x;s--){ unsigned v=c[t][s]+c[t][s-x]; if(v>=M[t]) v-=M[t]; c[t][s]=v; } }
    vector<int> res; vector<unsigned> d;
    for(int i=0;i<n;i++){
        int R=S-w[i]; if(R&1) continue; int T=R/2; bool ok=false;
        for(int t=0;t<2&&!ok;t++){
            d.assign(T+1,0);
            for(int s=0;s<=T;s++){ unsigned v=c[t][s]; if(s>=w[i]){ unsigned u=d[s-w[i]]; v = v>=u? v-u : v+(unsigned)M[t]-u; } d[s]=v; }
            if(d[T]) ok=true;
        }
        if(ok) res.push_back(i+1);
    }
    printf("%d\n",(int)res.size());
    for(size_t i=0;i<res.size();i++) printf("%d%c",res[i]," \n"[i+1==res.size()]);
}
