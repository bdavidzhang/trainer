#include <bits/stdc++.h>
using namespace std;
// Cells (i,c), 1-indexed, exist iff |c-N| <= i-1. 4-neighbour adjacency.
// The pyramid has exactly three leaves: top a=(1,N), corners b=(N,1), c=(N,2N-1).
// We build orderings of all cells in which every cell has an earlier and a later neighbour
// (so every prefix/suffix is connected), except that one leaf sits next to its neighbour,
// making exactly one cut invalid. Prefix stone counts move by <=1, so a cut with T/2 exists;
// several orderings guarantee that some such cut is not the invalid one whenever a solution exists.
static int N;
typedef pair<int,int> Cell;
static vector<Cell> rowOrder(){            // top -> right corner, left corner in the middle
    vector<Cell> o; o.push_back({1,N});
    for(int i=2;i<N;i++){
        for(int c=N-i+2;c<=N+i-2;c++) o.push_back({i,c});
        o.push_back({i,N-i+1}); o.push_back({i,N+i-1});
    }
    o.push_back({N,2}); o.push_back({N,1});
    for(int c=3;c<=2*N-1;c++) o.push_back({N,c});
    return o;
}
static vector<Cell> colOrder(){            // left corner -> right corner, top in the middle
    vector<Cell> o;
    for(int c=1;c<N;c++) for(int i=N;i>=N-c+1;i--) o.push_back({i,c});
    o.push_back({2,N}); o.push_back({1,N});
    for(int i=3;i<=N;i++) o.push_back({i,N});
    for(int c=N+1;c<=2*N-1;c++) for(int i=c-N+1;i<=N;i++) o.push_back({i,c});
    return o;
}
static vector<Cell> stairOrder(){          // top, down the left staircase to the left corner, then columns -> right corner
    vector<Cell> o; o.push_back({1,N});
    for(int i=2;i<=N;i++){ o.push_back({i,N-i+2}); o.push_back({i,N-i+1}); }
    for(int c=3;c<=N;c++) for(int i=N-c+3;i<=N;i++) o.push_back({i,c});
    for(int c=N+1;c<=2*N-1;c++) for(int i=c-N+1;i<=N;i++) o.push_back({i,c});
    return o;
}
static bool valid(const vector<string>&g,const vector<string>&lab){
    int Wd=2*N-1; int stones[2]={0,0}, cells[2]={0,0};
    for(int i=0;i<N;i++) for(int c=0;c<Wd;c++) if(g[i][c]!='#'){ int k=lab[i][c]-'A'; cells[k]++; if(g[i][c]=='C') stones[k]++; }
    if(stones[0]!=stones[1]||!cells[0]||!cells[1]) return false;
    vector<char> seen(N*Wd,0);
    for(int k=0;k<2;k++){
        int si=-1,sc=-1;
        for(int i=0;i<N&&si<0;i++) for(int c=0;c<Wd;c++) if(g[i][c]!='#'&&lab[i][c]=='A'+k){ si=i; sc=c; break; }
        vector<int> q; q.push_back(si*Wd+sc); seen[si*Wd+sc]=1; int cnt=0;
        static const int di[]={1,-1,0,0},dc[]={0,0,1,-1};
        for(size_t h=0;h<q.size();h++){
            int i=q[h]/Wd,c=q[h]%Wd; cnt++;
            for(int d=0;d<4;d++){ int ni=i+di[d],nc=c+dc[d];
                if(ni<0||ni>=N||nc<0||nc>=Wd||g[ni][nc]=='#'||lab[ni][nc]!='A'+k||seen[ni*Wd+nc]) continue;
                seen[ni*Wd+nc]=1; q.push_back(ni*Wd+nc); }
        }
        if(cnt!=cells[k]) return false;
    }
    return true;
}
vector<string> solveCase(int n,const vector<string>&g){
    N=n; int Wd=2*N-1; int T=0;
    for(auto &r:g) for(char ch:r) if(ch=='C') T++;
    if(T%2) return {};
    int H=T/2;
    vector<vector<Cell>> ords;
    for(int kind=0;kind<3;kind++){
        vector<Cell> o = kind==0?rowOrder():kind==1?colOrder():stairOrder();
        ords.push_back(o);
        if(kind!=1){ for(auto &x:o) x.second=2*N-x.second; ords.push_back(o); }
    }
    for(auto &o:ords){
        int n2=o.size(); int first=-1,last=-1,pre=0;
        for(int j=1;j<n2;j++){
            if(g[o[j-1].first-1][o[j-1].second-1]=='C') pre++;
            if(pre==H){ if(first<0) first=j; last=j; }
        }
        if(first<0) continue;
        for(int cut: {first,last}){
            vector<string> lab=g;
            for(int j=0;j<n2;j++) lab[o[j].first-1][o[j].second-1]= j<cut?'A':'B';
            if(valid(g,lab)) return lab;
            if(first==last) break;
        }
    }
    return {};
}
int main(){
    int n; if(scanf("%d",&n)!=1) return 0;
    vector<string> g(n); char buf[1024];
    for(int i=0;i<n;i++){ scanf("%s",buf); g[i]=buf; }
    auto r=solveCase(n,g);
    if(r.empty()) puts("impossible"); else for(auto &s:r) puts(s.c_str());
    return 0;
}
