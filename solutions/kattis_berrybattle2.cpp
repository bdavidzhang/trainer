#include <bits/stdc++.h>
using namespace std;
// Grandpa moves first and always takes a maximum window; Erik's move can never be worth more than
// grandpa's previous one, so Erik can at best tie, and he ties iff he always answers with a window of the
// same value, i.e. iff grandpa never takes the LAST window of the current maximum value v.
// Within a "phase" (current maximum = v) both players only take v-windows, so the phase is a normal-play
// impartial game ("take a window containing exactly v berries; whoever takes the last one wins") and Erik
// wants to be the one making the last move.  A move wipes 4 consecutive cells, which separates left and
// right parts, so Sprague-Grundy with an interval DP per cluster applies.  Erik moves to nim-sum 0 whenever
// possible; grandpa moves randomly, so he hands Erik a non-zero nim-sum almost immediately and from then
// on Erik keeps nim-sum 0 at grandpa's turns until the phase ends with Erik's move.
int N;
vector<char> B;            // 1 = berry
vector<int> wc;            // berries in window starting at i
vector<int> lst[5]; vector<int> wherei;
static void bucketMove(int i,int from,int to){
    int p=wherei[i]; int last=lst[from].back(); lst[from][p]=last; wherei[last]=p; lst[from].pop_back();
    wherei[i]=lst[to].size(); lst[to].push_back(i);
}
struct Comp{ int start,len; vector<unsigned char> g; };
vector<Comp> comps;
struct Iv{ int comp,l,r; };   // local [l,r) inside comp
map<int,Iv> live;             // key: global start
int phaseV=0; int X=0;
static inline int G(const Comp&c,int l,int r){ return c.g[l*(c.len+1)+r]; }
static void rebuild(int v){
    comps.clear(); live.clear(); X=0; phaseV=v;
    int i=0;
    while(i<N){
        if(!B[i]){ i++; continue; }
        int st=i, lastB=i, j=i+1;
        while(j<N && j-lastB<=3){ if(B[j]) lastB=j; j++; }
        int L=lastB-st+1;
        i=lastB+1;
        // any v-window here?
        vector<int> pre(L+1,0);
        for(int k=0;k<L;k++) pre[k+1]=pre[k]+B[st+k];
        bool any=false;
        for(int k=-3;k<L&&!any;k++){ int a=max(k,0), b=min(k+4,L); if(pre[b]-pre[a]==v) any=true; }
        if(!any) continue;
        Comp c; c.start=st; c.len=L; c.g.assign((L+1)*(L+1),0);
        vector<int> seen(L+8,-1); int stamp=0;
        for(int len=1;len<=L;len++){
            for(int l=0;l+len<=L;l++){
                int r=l+len; stamp++;
                for(int k=l-3;k<r;k++){
                    int a=max(k,l), b=min(k+4,r);
                    if(pre[b]-pre[a]!=v) continue;
                    int val=c.g[l*(L+1)+a]^c.g[b*(L+1)+r];
                    if(val<(int)seen.size()) seen[val]=stamp;
                }
                int mex=0; while(seen[mex]==stamp) mex++;
                c.g[l*(L+1)+r]=(unsigned char)mex;
            }
        }
        int id=comps.size();
        X^=c.g[0*(L+1)+L];
        comps.push_back(std::move(c));
        live[st]=Iv{id,0,L};
    }
}
static int curMax(){ for(int v=4;v>=1;v--) if(!lst[v].empty()) return v; return 0; }
static void syncPhase(){ int v=curMax(); if(v!=phaseV){ if(v>0) rebuild(v); else { phaseV=0; } } }
static void applyMove(int i){ // window [i,i+4), global 0-indexed start
    int firstB=-1;
    for(int k=i;k<i+4;k++) if(B[k]){ firstB=k; break; }
    if(firstB<0) return;
    if(wc[i]==phaseV){
        auto it=live.upper_bound(firstB);
        if(it!=live.begin()){
            --it;
            Iv iv=it->second; const Comp&c=comps[iv.comp];
            int gl=c.start+iv.l, gr=c.start+iv.r;
            if(firstB>=gl && firstB<gr){
                int a=max(i,gl)-c.start, b=min(i+4,gr)-c.start;
                X^=G(c,iv.l,iv.r);
                live.erase(it);
                if(a>iv.l){ X^=G(c,iv.l,a); live[c.start+iv.l]=Iv{iv.comp,iv.l,a}; }
                if(b<iv.r){ X^=G(c,b,iv.r); live[c.start+b]=Iv{iv.comp,b,iv.r}; }
            }
        }
    }
    for(int k=i;k<i+4;k++) if(B[k]){
        B[k]=0;
        for(int w=max(0,k-3); w<=min(N-4,k); w++){ bucketMove(w,wc[w],wc[w]-1); wc[w]--; }
    }
}
static mt19937 rng(712367);
static int erikMove(){ // returns window start (0-indexed) or -1 if no berries
    syncPhase();
    int v=phaseV; if(v==0) return -1;
    if(X!=0){
        for(auto&kv:live){
            const Iv&iv=kv.second; const Comp&c=comps[iv.comp];
            int g=G(c,iv.l,iv.r); int target=g^X;
            if(target>=g) continue;
            for(int k=iv.l-3;k<iv.r;k++){
                int a=max(k,iv.l), b=min(k+4,iv.r);
                if(a>=b) continue;
                int gs=min(max(c.start+k,0),N-4);
                if(wc[gs]!=v) continue;
                // the clamped window must remove exactly the berries of local [a,b)
                int ga=max(gs,c.start+iv.l)-c.start, gb=min(gs+4,c.start+iv.r)-c.start;
                if((G(c,iv.l,ga)^G(c,gb,iv.r))==target) return gs;
            }
        }
    }
    // nim-sum 0 (or nothing found): any maximum window
    return lst[v][rng()%lst[v].size()];
}
static void initGame(const string&s){
    N=s.size(); B.assign(N,0); for(int i=0;i<N;i++) B[i]=(s[i]=='b');
    int W=max(0,N-3); wc.assign(W,0); wherei.assign(W,0); for(int c=0;c<5;c++) lst[c].clear();
    for(int i=0;i<W;i++){ int c=B[i]+B[i+1]+B[i+2]+B[i+3]; wc[i]=c; wherei[i]=lst[c].size(); lst[c].push_back(i); }
    phaseV=0; X=0; comps.clear(); live.clear();
}
#ifndef LOCAL_SIM
int main(){
    int n; char *buf=(char*)malloc(1<<20);
    if(scanf("%d %s",&n,buf)!=2) return 0;
    initGame(string(buf));
    while(true){
        if(curMax()==0) break;         // grandpa's turn, no berries: grader stops
        int gi; if(scanf("%d",&gi)!=1) break;
        syncPhase();
        applyMove(gi-1);
        int e=erikMove();
        if(e<0) break;
        printf("%d\n",e+1); fflush(stdout);
        applyMove(e);
    }
    return 0;
}
#else
int main(int argc,char**argv){
    int games=argc>1?atoi(argv[1]):20; int n=argc>2?atoi(argv[2]):100000; unsigned seed=argc>3?atoi(argv[3]):1;
    mt19937 gen(seed); int wins=0; long long worst=0;
    for(int gm=0;gm<games;gm++){
        string s(n,'.'); vector<int> p(n); iota(p.begin(),p.end(),0); shuffle(p.begin(),p.end(),gen);
        for(int i=0;i<n/2;i++) s[p[i]]='b';
        initGame(s);
        long long ge=0,ee=0;
        while(true){
            int v=curMax(); if(v==0) break;
            int gi=lst[v][gen()%lst[v].size()];
            ge+=wc[gi]; syncPhase(); applyMove(gi);
            int e=erikMove(); if(e<0) break;
            if(e<0||e>n-4){ fprintf(stderr,"bad move\n"); return 1; }
            ee+=wc[e]; applyMove(e);
        }
        if(ee>=ge) wins++; else { worst=min(worst,ee-ge); fprintf(stderr,"loss game %d: %lld vs %lld\n",gm,ee,ge); }
    }
    printf("wins %d / %d (worst %lld)\n",wins,games,worst);
}
#endif
