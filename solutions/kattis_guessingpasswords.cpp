#include <bits/stdc++.h>
using namespace std;
// Rows = guesses plus the secret, columns = positions, edge = a known (yellow) character sits there.
// The y known characters are the colours of a proper edge colouring with y colours (Konig).
int N,M;
int Lc[105][105], Rc[105][105]; // Lc[row][colour]=column, Rc[col][colour]=row
int main(){
    scanf("%d %d",&N,&M);
    vector<string> g(N);
    for(auto&s:g){ static char b[205]; scanf("%s",b); s=b; }
    long long Sig; scanf("%lld",&Sig);
    int y=0; for(char c:g[0]) if(c=='Y') y++;
    vector<int> deg(M,0);
    for(int i=0;i<N;i++) for(int j=0;j<M;j++) if(g[i][j]=='Y') deg[j]++;
    bool ok=true;
    for(int j=0;j<M;j++) if(deg[j]>y) ok=false;
    vector<int> T;
    for(int j=0;j<M&&(int)T.size()<y;j++) if(deg[j]<y) T.push_back(j);
    if((int)T.size()<y) ok=false;
    if((long long)y+(long long)(N+1)*(M-y)>Sig) ok=false;
    if(!ok){ puts("Bugged!"); return 0; }
    string sec(M,'G'); for(int j:T) sec[j]='Y';
    g.push_back(sec);
    memset(Lc,-1,sizeof Lc); memset(Rc,-1,sizeof Rc);
    for(int u=0;u<=N;u++) for(int v=0;v<M;v++) if(g[u][v]=='Y'){
        int a=0,b=0;
        while(Lc[u][a]!=-1) a++;
        while(Rc[v][b]!=-1) b++;
        if(a!=b){
            // flip the a/b alternating path starting at column v with colour a
            vector<pair<int,int>> path; // (row,col) edges
            int cv=v, col=a;
            while(true){
                // from column cv follow colour `col` to a row
                int r=Rc[cv][col]; if(r==-1) break;
                path.push_back({r,cv});
                int oc=col^a^b;
                int nv=Lc[r][oc]; if(nv==-1) break;
                path.push_back({r,nv});
                cv=nv;
            }
            // edges alternate colours a,b,a,b...; erase then reinsert swapped
            for(size_t i=0;i<path.size();i++){ int c=(i%2==0)?a:b; Lc[path[i].first][c]=-1; Rc[path[i].second][c]=-1; }
            for(size_t i=0;i<path.size();i++){ int c=(i%2==0)?b:a; Lc[path[i].first][c]=path[i].second; Rc[path[i].second][c]=path[i].first; }
        }
        Lc[u][a]=v; Rc[v][a]=u;
    }
    long long fresh=y;
    for(int u=0;u<=N;u++){
        vector<long long> row(M,0);
        for(int c=0;c<y;c++) row[Lc[u][c]]=c+1;
        for(int v=0;v<M;v++){ if(row[v]==0) row[v]=++fresh; printf("%lld ",row[v]); }
        puts("");
    }
}
