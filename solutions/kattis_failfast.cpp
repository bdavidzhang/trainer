#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
int n;
vector<int> dsu;
int find(int x){ while(dsu[x]!=x){ dsu[x]=dsu[dsu[x]]; x=dsu[x]; } return x; }
int main(){
    scanf("%d",&n);
    vector<ld> c(n+1),p(n+1); vector<int> d(n+1),nxt(n+1,0),tail(n+1);
    dsu.resize(n+1);
    for(int i=1;i<=n;i++){ double pp; int cc; scanf("%d %lf %d",&cc,&pp,&d[i]); c[i]=cc; p[i]=pp; }
    for(int i=0;i<=n;i++){ dsu[i]=i; tail[i]=i; }
    // minimise sum c_i * prod_{j before i} p_j ; block ratio c/(1-p), smaller goes first
    auto ratio=[&](int g){ return c[g]/(1-p[g]); };
    set<pair<ld,int>> S;
    for(int i=1;i<=n;i++) S.insert({ratio(i),i});
    while(!S.empty()){
        int g=S.begin()->second; S.erase(S.begin());
        int h=find(d[g]);           // block containing g's prerequisite (0 = virtual root)
        if(h!=0) S.erase({ratio(h),h});
        nxt[tail[h]]=g; tail[h]=tail[g];
        dsu[g]=h;
        if(h!=0){
            c[h]=c[h]+p[h]*c[g]; p[h]=p[h]*p[g];
            S.insert({ratio(h),h});
        }
    }
    for(int x=nxt[0];x;x=nxt[x]) printf("%d\n",x);
}
