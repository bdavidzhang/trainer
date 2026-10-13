#include <bits/stdc++.h>
using namespace std;
// Graph: two lines (odd side L1, even side L2) joined by two rungs -> one cycle with 4 tails.
// Each tail has two useful states: "free" (optimal stabbing of its internal intervals with cuts pushed
// towards the root) or "paid" (+1 cut at the root edge). Enumerate 16 states; the paths still unhit
// become circular arcs on the cycle -> min circular stabbing via binary lifting.
int n,m,c1,c2,N,p1,p2,K,C;
struct Arc{int l,r,tm;};
int main(){
    scanf("%d %d %d %d",&n,&m,&c1,&c2);
    N=n/2; p1=(c1+1)/2; p2=(c2+1)/2; K=p2-p1; C=2*K+2;
    int len[4]={p1-1,N-p2,p1-1,N-p2};
    vector<pair<int,int>> internal[4];
    struct P{int l,r;int ext[4];};
    vector<P> paths; paths.reserve(m);
    auto clampK=[&](int v){return max(0,min(K,v));};
    for(int i=0;i<m;i++){
        int a,b; scanf("%d %d",&a,&b);
        if((a&1)==(b&1)){
            int L=(a&1)?0:1; int x=(a+1)/2,y=(b+1)/2; if(x>y)swap(x,y);
            if(y<=p1) internal[L*2].push_back({p1-y,p1-1-x});
            else if(x>=p2) internal[L*2+1].push_back({x-p2,y-1-p2});
            else{
                P q; memset(q.ext,0,sizeof q.ext);
                q.ext[L*2]=max(0,p1-x); q.ext[L*2+1]=max(0,y-p2);
                int lo=max(x,p1),hi=min(y,p2);
                if(L==0){q.l=lo-p1;q.r=hi-p1-1;} else {q.l=K+1+p2-hi;q.r=K+p2-lo;}
                paths.push_back(q);
            }
        } else {
            int c; scanf("%d",&c);
            if(!(a&1)) swap(a,b);
            int x=(a+1)/2,y=(b+1)/2,p=(c+1)/2;
            P q;
            q.ext[0]=max(0,p1-x); q.ext[1]=max(0,x-p2); q.ext[2]=max(0,p1-y); q.ext[3]=max(0,y-p2);
            if(p==p1){ int R=2*K+1; q.l=R-clampK(y-p1); q.r=R+clampK(x-p1); }
            else { q.l=K-clampK(p2-x); q.r=K+clampK(p2-y); }
            paths.push_back(q);
        }
    }
    const int INF=INT_MAX;
    vector<int> cuts[4]; int mt[4]; int base=0;
    for(int t=0;t<4;t++){
        auto&v=internal[t];
        sort(v.begin(),v.end(),[](const pair<int,int>&a,const pair<int,int>&b){return a.first>b.first;});
        int c=INF;
        for(auto&iv:v){ if(c<=iv.second) continue; c=iv.first; cuts[t].push_back(c); }
        mt[t]=c; base+=cuts[t].size();
    }
    vector<Arc> arcs;
    for(auto&q:paths){
        bool hit=false; int tm=0;
        for(int t=0;t<4;t++) if(q.ext[t]>0){ tm|=1<<t; if(mt[t]!=INF && mt[t]<=q.ext[t]-1) hit=true; }
        if(!hit) arcs.push_back({q.l,q.r,tm});
    }
    int S=2*C;
    const int LOG=19;
    vector<int> g(S+1);
    vector<vector<int>> up(LOG, vector<int>(S+1));
    // returns min cuts on cycle for mask; fills res if wanted
    auto solveCycle=[&](int mask, vector<int>*res)->int{
        fill(g.begin(),g.end(),S);
        bool any=false;
        for(auto&a:arcs) if(!(a.tm&mask)){
            any=true;
            g[a.l]=min(g[a.l],a.r);
            if(a.l+C<S) g[a.l+C]=min(g[a.l+C],min(S,a.r+C));
        }
        if(!any) return 0;
        // g(i)=min r over arcs with l>i
        { int cur=S; for(int i=S-1;i>=0;i--){ int own=g[i]; g[i]=cur; cur=min(cur,own);} g[S]=S; }
        up[0]=g;
        for(int j=1;j<LOG;j++){ auto&u=up[j]; auto&d=up[j-1]; for(int i=0;i<=S;i++) u[i]=d[d[i]]; }
        int best=INF,bi=-1;
        for(int i=0;i<C;i++){
            int cur=i,cnt=1,lim=i+C;
            for(int j=LOG-1;j>=0;j--) if(up[j][cur]<lim){cur=up[j][cur];cnt+=1<<j;}
            if(cnt<best){best=cnt;bi=i;}
        }
        if(res){ int cur=bi; res->push_back(cur); while(g[cur]<bi+C){cur=g[cur];res->push_back(cur%C);} }
        return best;
    };
    int best=INF,bestMask=-1;
    vector<int> order(16); iota(order.begin(),order.end(),0);
    sort(order.begin(),order.end(),[](int a,int b){return __builtin_popcount(a)<__builtin_popcount(b);});
    for(int mask:order){
        bool ok=true;
        for(int t=0;t<4;t++) if((mask>>t&1)&&(len[t]==0||mt[t]==0)) ok=false;
        if(!ok) continue;
        int cost=base+__builtin_popcount(mask);
        if(cost>=best) continue;
        cost+=solveCycle(mask,nullptr);
        if(cost<best){best=cost;bestMask=mask;}
    }
    vector<int> cyc; solveCycle(bestMask,&cyc);
    vector<pair<int,int>> out;
    for(int t=0;t<4;t++){
        vector<int> ds=cuts[t]; if(bestMask>>t&1) ds.push_back(0);
        int line=t/2, side=t%2;
        for(int d:ds){
            int a=side==0?p1-d-1:p2+d; // positions a,a+1
            if(line==0) out.push_back({2*a-1,2*a+1}); else out.push_back({2*a,2*a+2});
        }
    }
    for(int idx:cyc){
        if(idx<K){int a=p1+idx; out.push_back({2*a-1,2*a+1});}
        else if(idx==K) out.push_back({2*p2-1,2*p2});
        else if(idx<=2*K){int q=p2+K-idx; out.push_back({2*q,2*q+2});}
        else out.push_back({2*p1-1,2*p1});
    }
    printf("%d\n",(int)out.size());
    for(auto&e:out) printf("%d %d\n",e.first,e.second);
}
