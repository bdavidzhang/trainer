#include <bits/stdc++.h>
using namespace std;
int n,m; int col[100][100]; // 0 none, else mask allowed: bits R=1,Y=2,B=4 ; X=8
bool painted[100][100]; static bool vis[100][100][100];
vector<int> adj[100];
int main(){
    int r,b,y; scanf("%d %d %d %d %d",&n,&m,&r,&b,&y); r--;b--;y--;
    map<char,int> mp={{'R',1},{'Y',2},{'B',4},{'O',3},{'G',6},{'P',5},{'X',8}};
    int need=0;
    for(int i=0;i<m;i++){int u,v;char c;scanf("%d %d %c",&u,&v,&c);u--;v--;col[u][v]=col[v][u]=mp[c];adj[u].push_back(v);adj[v].push_back(u); if(c!='X')need++;}
    // state p[0]=red,p[1]=yellow,p[2]=blue
    vector<array<int,3>> q; q.push_back({r,y,b}); vis[r][y][b]=1;
    int got=0;
    for(size_t h=0;h<q.size();h++){
        array<int,3> s=q[h];
        for(int mask=1;mask<8;mask++){
            int u=-1; bool ok=true;
            for(int i=0;i<3;i++) if(mask>>i&1){ if(u<0)u=s[i]; else if(u!=s[i]) ok=false; }
            if(!ok)continue;
            for(int v:adj[u]){
                int c=col[u][v];
                if(c!=8 && c!=mask) continue;
                if(c!=8 && !painted[u][v]){painted[u][v]=painted[v][u]=true;got++;}
                array<int,3> t=s; for(int i=0;i<3;i++) if(mask>>i&1) t[i]=v;
                if(!vis[t[0]][t[1]][t[2]]){vis[t[0]][t[1]][t[2]]=1;q.push_back(t);}
            }
        }
    }
    printf("%d\n",got==need?1:0);
}
