#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
int g[8][8];
int posOf[66];
int kd[64][64];
vector<int> adj[64];
int rs[8], cs[8];       // current line sums
int re[8][2], ce[8][2]; // empty cells per line, by parity of the label they must receive
u64 un[2];              // unassigned missing labels, by parity (bit = label/2, so label 64 fits)
struct Gap{int k1,c1,k2,c2;}; // labels k1+1..k2-1 are missing; c2=-1 for the open tail (k2=65)
vector<Gap> gaps;
static inline bool lineOk(int s,int e0,int e1){
    int need=260-s, lo=0, hi=0;
    for(int p=0;p<2;p++){
        int e=p?e1:e0; if(!e) continue;
        u64 m=un[p];
        if(__builtin_popcountll(m)<e) return false;
        u64 a=m; for(int i=0;i<e;i++){ lo+=2*__builtin_ctzll(a)+p; a&=a-1; }
        a=m; for(int i=0;i<e;i++){ int b=63-__builtin_clzll(a); hi+=2*b+p; a^=1ULL<<b; }
    }
    return lo<=need && need<=hi;
}
static inline bool allOk(){
    for(int i=0;i<8;i++){
        if(!lineOk(rs[i],re[i][0],re[i][1])) return false;
        if(!lineOk(cs[i],ce[i][0],ce[i][1])) return false;
    }
    return true;
}
bool gdone[70];
int openEnd[64];   // >0 if the cell is a still-open path endpoint (current head or an unfinished gap's end)
bool tailOpen;     // the open-ended last gap is not finished yet
// every empty cell still needs two neighbours on the path (one if it may be the final cell 64)
static inline bool degOk(){
    int ones=0;
    for(int x=0;x<64;x++) if(g[x/8][x%8]==-1){
        int dg=0;
        for(int y:adj[x]) if(g[y/8][y%8]==-1 || openEnd[y]>0) dg++;
        if(dg==0) return false;
        if(dg==1){ if(!tailOpen || ++ones>1) return false; }
    }
    return true;
}
const int CAP=64;
// number of ways (capped) to walk from c (label k) to the end of gap G through empty cells
int cntPaths(const Gap& G,int k,int c,int cap){
    if(k==G.k2-1) return (G.c2<0 || kd[c][G.c2]==1) ? 1 : 0;
    int left=G.k2-(k+1), tot=0;
    for(int d:adj[c]) if(g[d/8][d%8]==-1){
        if(G.c2>=0){ int dd=kd[d][G.c2]; if(dd>left || ((left-dd)&1)) continue; }
        g[d/8][d%8]=-2;
        tot+=cntPaths(G,k+1,d,cap-tot);
        g[d/8][d%8]=-1;
        if(tot>=cap) break;
    }
    return tot;
}
bool dfs(int gi,int k,int c);
bool nextGap(){
    // forward checking + most-constrained-first: pick the open gap with the fewest fillings
    int best=-1, bc=INT_MAX;
    for(int i=0;i<(int)gaps.size();i++) if(!gdone[i]){
        const Gap& G=gaps[i];
        int len=G.k2-G.k1-1, c;
        if(len<=10 && G.c2>=0){ c=cntPaths(G,G.k1,G.c1,CAP); if(c==0) return false; if(c>=CAP) c=CAP+len; }
        else c=CAP+len+(G.c2<0?100:0);
        if(c<bc){bc=c;best=i;}
    }
    if(best<0){
        for(int i=0;i<8;i++) if(rs[i]!=260||cs[i]!=260) return false;
        return true;
    }
    gdone[best]=true;
    if(dfs(best,gaps[best].k1,gaps[best].c1)) return true;
    gdone[best]=false;
    return false;
}
bool dfs(int gi,int k,int c){ // inside gap gi, label k is at cell c
    const Gap& G=gaps[gi];
    if(k==G.k2-1){
        if(G.c2>=0 && kd[c][G.c2]!=1) return false;
        bool wasTail=tailOpen;
        openEnd[c]--; if(G.c2>=0) openEnd[G.c2]--; else tailOpen=false;
        bool ok=degOk() && nextGap();
        openEnd[c]++; if(G.c2>=0) openEnd[G.c2]++; tailOpen=wasTail;
        return ok;
    }
    int nk=k+1, p=nk&1, left=G.k2-nk;
    int cand[8],key[8],n=0;
    for(int d:adj[c]) if(g[d/8][d%8]==-1){
        if(G.c2>=0){ int dd=kd[d][G.c2]; if(dd>left || ((left-dd)&1)) continue; }
        int w=0; for(int e:adj[d]) if(g[e/8][e%8]==-1) w++;
        cand[n]=d; key[n]=w; n++;
    }
    for(int i=1;i<n;i++) for(int j=i;j>0&&key[j]<key[j-1];j--){swap(key[j],key[j-1]);swap(cand[j],cand[j-1]);}
    for(int i=0;i<n;i++){
        int d=cand[i], r=d/8, cc=d%8;
        g[r][cc]=nk; rs[r]+=nk; cs[cc]+=nk; re[r][p]--; ce[cc][p]--; un[p]^=1ULL<<(nk>>1);
        openEnd[c]--; openEnd[d]++;
        bool ok=allOk() && degOk() && dfs(gi,nk,d);
        openEnd[c]++; openEnd[d]--;
        if(ok) return true;
        g[r][cc]=-1; rs[r]-=nk; cs[cc]-=nk; re[r][p]++; ce[cc][p]++; un[p]^=1ULL<<(nk>>1);
    }
    return false;
}
int main(){
    memset(posOf,-1,sizeof posOf);
    int start=-1;
    for(int i=0;i<8;i++)for(int j=0;j<8;j++){
        scanf("%d",&g[i][j]);
        if(g[i][j]>0){ posOf[g[i][j]]=i*8+j; rs[i]+=g[i][j]; cs[j]+=g[i][j]; if(g[i][j]==1) start=i*8+j; }
    }
    int dr[8]={1,1,-1,-1,2,2,-2,-2}, dc[8]={2,-2,2,-2,1,-1,1,-1};
    for(int a=0;a<64;a++) for(int d=0;d<8;d++){
        int r=a/8+dr[d], c=a%8+dc[d];
        if(r>=0&&r<8&&c>=0&&c<8) adj[a].push_back(r*8+c);
    }
    for(int a=0;a<64;a++){
        for(int b=0;b<64;b++) kd[a][b]=1000;
        kd[a][a]=0; queue<int> q; q.push(a);
        while(!q.empty()){int u=q.front();q.pop(); for(int v:adj[u]) if(kd[a][v]>kd[a][u]+1){kd[a][v]=kd[a][u]+1;q.push(v);}}
    }
    for(int k=1;k<=64;k++) if(posOf[k]<0) un[k&1]|=1ULL<<(k>>1);
    int sc=(start/8+start%8)&1; // cells of start's colour get odd labels
    for(int i=0;i<8;i++)for(int j=0;j<8;j++) if(g[i][j]==-1){
        int p=(((i+j)&1)==sc)?1:0;
        re[i][p]++; ce[j][p]++;
    }
    int last=1;
    for(int k=2;k<=64;k++) if(posOf[k]>=0){
        if(k-last>=2) gaps.push_back({last,posOf[last],k,posOf[k]});
        last=k;
    }
    if(last<64) gaps.push_back({last,posOf[last],65,-1});
    for(auto&G:gaps){ openEnd[G.c1]++; if(G.c2>=0) openEnd[G.c2]++; else tailOpen=true; }
    nextGap();
    for(int i=0;i<8;i++){ for(int j=0;j<8;j++) printf("%d%c",g[i][j],j==7?'\n':' '); }
}
