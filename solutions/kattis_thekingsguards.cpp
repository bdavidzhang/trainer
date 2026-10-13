#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
const int W=5;
struct BS{ u64 w[W]; };
struct State{
    int cid[300]; BS cmask[300]; int matchC[300]; int matchG[300];
};
int n,r,g;
BS adjG[300];
static State S,T;
int via[300];
// find augmenting path for free guard s in state st; apply on success
bool augment(State&st,int s){
    BS U; for(int i=0;i<W;i++) U.w[i]=~0ULL;
    vector<int> q; q.push_back(s);
    for(size_t h=0;h<q.size();h++){
        int x=q[h];
        for(int wi=0;wi<W;wi++){
            u64 bits=adjG[x].w[wi]&U.w[wi];
            while(bits){
                int v=wi*64+__builtin_ctzll(bits);
                int c=st.cid[v];
                for(int k=0;k<W;k++) U.w[k]&=~st.cmask[c].w[k];
                bits&=U.w[wi];
                via[c]=x;
                if(st.matchC[c]<0){
                    int cc=c,xx=x;
                    while(true){
                        int prev=st.matchG[xx];
                        st.matchC[cc]=xx; st.matchG[xx]=cc;
                        if(xx==s) break;
                        cc=prev; xx=via[cc];
                    }
                    return true;
                }
                q.push_back(st.matchC[c]);
            }
        }
    }
    return false;
}
int main(){
    scanf("%d %d %d",&n,&r,&g);
    vector<array<int,3>> E(r);
    for(auto&e:E){scanf("%d %d %d",&e[1],&e[2],&e[0]);e[1]--;e[2]--;}
    sort(E.begin(),E.end());
    memset(adjG,0,sizeof adjG);
    for(int i=0;i<g;i++){
        int k;scanf("%d",&k);
        while(k--){int v;scanf("%d",&v);v--;adjG[i].w[v>>6]|=1ULL<<(v&63);}
    }
    memset(&S,0,sizeof S);
    for(int v=0;v<n;v++){S.cid[v]=v;S.cmask[v].w[v>>6]|=1ULL<<(v&63);S.matchC[v]=-1;}
    for(int i=0;i<g;i++)S.matchG[i]=-1;
    for(int i=0;i<g;i++) if(!augment(S,i)){puts("-1");return 0;}
    int comps=n; long long cost=0;
    for(auto&e:E){
        if(comps==g) break;
        int A=S.cid[e[1]],B=S.cid[e[2]];
        if(A==B) continue;
        if(S.matchC[A]>=0 && S.matchC[B]>=0){
            T=S;
            int gb=T.matchC[B];
            for(int v=0;v<n;v++) if(T.cid[v]==B) T.cid[v]=A;
            for(int k=0;k<W;k++) T.cmask[A].w[k]|=T.cmask[B].w[k];
            T.matchC[B]=-1; T.matchG[gb]=-1;
            if(!augment(T,gb)) continue;
            S=T;
        } else {
            int gb=S.matchC[B];
            for(int v=0;v<n;v++) if(S.cid[v]==B) S.cid[v]=A;
            for(int k=0;k<W;k++) S.cmask[A].w[k]|=S.cmask[B].w[k];
            S.matchC[B]=-1;
            if(gb>=0){S.matchC[A]=gb;S.matchG[gb]=A;}
        }
        cost+=e[0]; comps--;
    }
    if(comps!=g) puts("-1"); else printf("%lld\n",cost);
}
