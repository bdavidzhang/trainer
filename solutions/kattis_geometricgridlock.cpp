#include <bits/stdc++.h>
using namespace std;
// ---- pentomino tiling search on an R x C board, row-major first-empty-cell DFS ----
static const char* NAMES="FILNPTUVWXYZ";
static const int BASE[12][5][2]={
 {{0,1},{0,2},{1,0},{1,1},{2,1}}, {{0,0},{0,1},{0,2},{0,3},{0,4}}, {{0,0},{1,0},{2,0},{3,0},{3,1}},
 {{0,1},{1,1},{2,0},{2,1},{3,0}}, {{0,0},{0,1},{1,0},{1,1},{2,0}}, {{0,0},{0,1},{0,2},{1,1},{2,1}},
 {{0,0},{0,2},{1,0},{1,1},{1,2}}, {{0,0},{1,0},{2,0},{2,1},{2,2}}, {{0,0},{1,0},{1,1},{2,1},{2,2}},
 {{0,1},{1,0},{1,1},{1,2},{2,1}}, {{0,1},{1,0},{1,1},{2,1},{3,1}}, {{0,0},{0,1},{1,1},{2,1},{2,2}}};
struct Ori{int shape; int d[5][2];};
static vector<Ori> ORIS;
static void buildOris(){
    set<vector<pair<int,int>>> seen;
    for(int s=0;s<12;s++){
        vector<pair<int,int>> p; for(int i=0;i<5;i++)p.push_back({BASE[s][i][0],BASE[s][i][1]});
        for(int f=0;f<2;f++){
            for(int r=0;r<4;r++){
                for(auto&q:p)q={q.second,-q.first};
                vector<pair<int,int>> t=p; sort(t.begin(),t.end());
                auto o=t[0]; for(auto&q:t){q.first-=o.first;q.second-=o.second;} // anchor = first cell in row-major order
                if(seen.insert(t).second){ Ori x; x.shape=s; for(int i=0;i<5;i++){x.d[i][0]=t[i].first;x.d[i][1]=t[i].second;} ORIS.push_back(x); }
            }
            for(auto&q:p)q.second=-q.second;
        }
    }
}
struct Board{
    int R,C; bool wrap; vector<int> extL,extR; // shapes adjacent beyond left/right border per row (-1 none)
    vector<int> id,shp; int nid; long long nodes,limit; vector<int> order;
    Board(int R_,int C_,bool w):R(R_),C(C_),wrap(w),extL(R_,-1),extR(R_,-1),id(R_*C_,-1),shp(R_*C_,-1),nid(0),nodes(0),limit(LLONG_MAX){
        order.resize(ORIS.size()); iota(order.begin(),order.end(),0); }
    bool conflict(int r,int c,int s,int me){
        static const int dr[4]={-1,1,0,0},dc[4]={0,0,-1,1};
        for(int k=0;k<4;k++){
            int nr=r+dr[k],nc=c+dc[k];
            if(nr<0||nr>=R)continue;
            if(nc<0||nc>=C){
                if(wrap){ int w=nr*C+(nc<0?C-1:0); if(id[w]>=0&&shp[w]==s) return true; }
                else if((nc<0?extL[nr]:extR[nr])==s) return true;
                continue;
            }
            int w=nr*C+nc; if(id[w]>=0&&id[w]!=me&&shp[w]==s) return true;
        }
        return false;
    }
    // returns 1 solved, 0 exhausted, -1 node limit hit
    int dfs(int from){
        int p=from; while(p<R*C&&id[p]>=0)p++;
        if(p==R*C) return 1;
        if(++nodes>limit) return -1;
        int r=p/C,c=p%C;
        for(int oi:order){
            const Ori&o=ORIS[oi]; bool ok=true; int cells[5];
            for(int i=0;i<5&&ok;i++){ int rr=r+o.d[i][0],cc=c+o.d[i][1];
                if(rr>=R||cc<0||cc>=C||id[rr*C+cc]>=0) ok=false; else cells[i]=rr*C+cc; }
            if(!ok)continue;
            int me=nid++;
            for(int i=0;i<5;i++){id[cells[i]]=me;shp[cells[i]]=o.shape;}
            bool bad=false;
            for(int i=0;i<5&&!bad;i++) bad=conflict(cells[i]/C,cells[i]%C,o.shape,me);
            if(!bad){ int res=dfs(p+1); if(res!=0) return res; }
            for(int i=0;i<5;i++){id[cells[i]]=-1;shp[cells[i]]=-1;}
            nid--;
        }
        return 0;
    }
};
// Tile an H x 5m board (H rows). Returns empty vector if impossible.
static vector<string> build(int H,int m){
    vector<string> g;
    auto render=[&](Board&b,vector<string>&rows){ for(int r=0;r<H;r++)for(int c=0;c<b.C;c++)rows[r]+=NAMES[b.shp[r*b.C+c]]; };
    if(H==1){ if(m==1) g.push_back("IIIII"); return g; }
    if(H==2){
        // 2x5 is impossible (every split gives two equal shapes). Use periodic 2x10 blocks, plus one 2x15 block when m is odd.
        if(m==1) return g;
        vector<string> rows(H);
        Board a(H,10,true); a.dfs(0);
        int na = (m%2==0)? m/2 : (m-3)/2;
        for(int i=0;i<na;i++) render(a,rows);
        if(m%2){
            Board b(H,15,false);
            if(na>0) for(int r=0;r<H;r++) b.extL[r]=a.shp[r*10+9];
            b.dfs(0); render(b,rows);
        }
        return rows;
    }
    // H >= 3: a single H x 5 slab whose left and right borders are compatible with each other, repeated m times.
    Board s(H,5,true);
    if(s.dfs(0)!=1) return g;
    vector<string> rows(H);
    for(int i=0;i<m;i++) render(s,rows);
    return rows;
}
int main(){
    buildOris();
    int h,w; if(scanf("%d %d",&h,&w)!=2) return 0;
    if((long long)h*w%5){ puts("no"); return 0; }
    vector<string> g; bool tr=false;
    if(w%5==0) g=build(h,w/5);
    if(g.empty()&&h%5==0){ g=build(w,h/5); tr=true; }
    if(g.empty()){ puts("no"); return 0; }
    puts("yes");
    if(!tr){ for(auto&r:g) puts(r.c_str()); }
    else { for(int i=0;i<h;i++){ string r; for(int j=0;j<w;j++) r+=g[j][i]; puts(r.c_str()); } }
}
