#include <bits/stdc++.h>
using namespace std;
// Find a "CEO" v (deg<=15) and <=8 of its neighbours S that dominate all other vertices.
// Enumerate the colourings of S up to colour symmetry (<= (3^7+1)/2 = 1094). Then every other vertex
// (the CEO included, since it sees all of S) has at most two colours left -> unit propagation + 2-SAT.
const int MAXN=1000;
typedef bitset<MAXN> BS;
int n,m;
vector<int> adj[MAXN];
BS closedNb[MAXN];
vector<int> S;
int allowed[MAXN];
// 2-SAT
int nv; vector<int> g[2*MAXN];
int idx_[2*MAXN], low_[2*MAXN], comp_[2*MAXN], timer_, ncomp; bool onst[2*MAXN]; vector<int> st;
void tarjan(int u){
    idx_[u]=low_[u]=++timer_; st.push_back(u); onst[u]=true;
    for(int w:g[u]){
        if(!idx_[w]){ tarjan(w); low_[u]=min(low_[u],low_[w]); }
        else if(onst[w]) low_[u]=min(low_[u],idx_[w]);
    }
    if(low_[u]==idx_[u]){
        while(true){ int w=st.back(); st.pop_back(); onst[w]=false; comp_[w]=ncomp; if(w==u) break; }
        ncomp++;
    }
}
int colS[8];
int finalCol[MAXN];
bool solveWith(){
    for(int i=0;i<n;i++) allowed[i]=7;
    vector<int> q;
    for(size_t i=0;i<S.size();i++){ allowed[S[i]]=1<<colS[i]; q.push_back(S[i]); }
    vector<char> done(n,0);
    for(size_t h=0;h<q.size();h++){
        int u=q[h]; if(done[u]) continue; done[u]=1;
        int c=allowed[u];
        for(int w:adj[u]){
            if(allowed[w]&c){
                allowed[w]&=~c;
                if(!allowed[w]) return false;
                if(__builtin_popcount(allowed[w])==1) q.push_back(w);
            }
        }
    }
    // remaining vertices: 2 colours (3 colours cannot happen for dominated vertices; treat defensively)
    vector<int> id(n,-1); vector<int> vs;
    for(int u=0;u<n;u++) if(__builtin_popcount(allowed[u])>=2){
        if(__builtin_popcount(allowed[u])==3) allowed[u]=3; // isolated from S: only possible in degenerate input
        id[u]=vs.size(); vs.push_back(u);
    }
    nv=vs.size();
    for(int i=0;i<2*nv;i++){ g[i].clear(); idx_[i]=0; onst[i]=false; }
    auto colOf=[&](int u,int t){ // t=0: low colour, t=1: high colour
        int a=allowed[u]; int lowc=__builtin_ctz(a); int highc=31-__builtin_clz(a);
        return t==0?lowc:highc;
    };
    for(int i=0;i<nv;i++){
        int u=vs[i];
        for(int w:adj[u]){
            int j=id[w]; if(j<0||j<i) continue;
            for(int a=0;a<2;a++) for(int b=0;b<2;b++) if(colOf(u,a)==colOf(w,b)){
                // not (u=a and w=b): (u=a) -> (w=!b), (w=b) -> (u=!a)
                g[2*i+a].push_back(2*j+(b^1));
                g[2*j+b].push_back(2*i+(a^1));
            }
        }
    }
    timer_=0; ncomp=0; st.clear();
    for(int i=0;i<2*nv;i++) if(!idx_[i]) tarjan(i);
    for(int i=0;i<nv;i++) if(comp_[2*i]==comp_[2*i+1]) return false;
    for(int u=0;u<n;u++) if(id[u]<0) finalCol[u]=__builtin_ctz(allowed[u]);
    for(int i=0;i<nv;i++){
        int t = comp_[2*i]<comp_[2*i+1] ? 0 : 1; // Tarjan: smaller comp index = later in topological order
        finalCol[vs[i]]=colOf(vs[i],t);
    }
    return true;
}
bool rec(int i,int mx){
    if(i==(int)S.size()) return solveWith();
    for(int c=0;c<=min(2,mx+1);c++){
        bool ok=true;
        for(int j=0;j<i;j++) if(colS[j]==c && closedNb[S[i]][S[j]]){ ok=false;break; }
        if(!ok) continue;
        colS[i]=c;
        if(rec(i+1,max(mx,c))) return true;
    }
    return false;
}
int main(){
    if(scanf("%d %d",&n,&m)!=2) return 0;
    for(int i=0;i<n;i++) closedNb[i][i]=1;
    for(int i=0;i<m;i++){
        int a,b; scanf("%d %d",&a,&b); a--;b--;
        if(a==b||closedNb[a][b]) continue;
        closedNb[a][b]=closedNb[b][a]=1; adj[a].push_back(b); adj[b].push_back(a);
    }
    BS all; for(int i=0;i<n;i++) all[i]=1;
    bool found=false;
    static BS cov[1<<15];
    for(int v=0;v<n&&!found;v++){
        int d=adj[v].size();
        if(d>15||d==0) continue;
        BS need=all; need[v]=0;
        BS un; for(int w:adj[v]) un|=closedNb[w];
        if((un&need)!=need) continue;
        int best=-1,bestPc=9;
        cov[0].reset();
        for(int mask=1;mask<(1<<d);mask++){
            int lb=__builtin_ctz(mask);
            cov[mask]=cov[mask&(mask-1)]|closedNb[adj[v][lb]];
            int pc=__builtin_popcount(mask);
            if(pc<bestPc && (cov[mask]&need)==need){ best=mask; bestPc=pc; }
        }
        if(best>=0){
            found=true;
            for(int i=0;i<d;i++) if(best>>i&1) S.push_back(adj[v][i]);
        }
    }
    if(!found){
        // not expected (guaranteed structure); fall back to a plain backtracking-free answer
        printf("Impossible\n"); return 0;
    }
    if(rec(0,-1)){
        for(int i=0;i<n;i++) printf("%d%c",finalCol[i]+1,i==n-1?'\n':' ');
    } else printf("Impossible\n");
}
