#include <bits/stdc++.h>
using namespace std;
int n,k;
int g[100][100];
bool usedCol[100][101];
int matchVal[101];
bool vis[101];
bool tryK(int c){
    for(int v=1;v<=n;v++){
        if(usedCol[c][v]||vis[v]) continue;
        vis[v]=true;
        if(matchVal[v]<0||tryK(matchVal[v])){ matchVal[v]=c; return true; }
    }
    return false;
}
int main(){
    scanf("%d %d",&n,&k);
    bool ok=true;
    for(int i=0;i<k;i++){
        vector<bool> seen(n+1,false);
        for(int j=0;j<n;j++){
            scanf("%d",&g[i][j]);
            int v=g[i][j];
            if(v<1||v>n){ ok=false; continue; }
            if(seen[v]) ok=false;
            seen[v]=true;
            if(usedCol[j][v]) ok=false;
            usedCol[j][v]=true;
        }
    }
    if(!ok){ puts("no"); return 0; }
    for(int i=k;i<n;i++){
        fill(matchVal,matchVal+n+1,-1);
        for(int c=0;c<n;c++){
            fill(vis,vis+n+1,false);
            if(!tryK(c)){ puts("no"); return 0; }
        }
        for(int v=1;v<=n;v++){ g[i][matchVal[v]]=v; usedCol[matchVal[v]][v]=true; }
    }
    puts("yes");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) printf("%d%c",g[i][j],j+1<n?' ':'\n');
    }
}
