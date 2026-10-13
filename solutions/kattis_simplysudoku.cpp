#include <bits/stdc++.h>
using namespace std;
int g[9][9];
bool can(int r,int c,int d){
    if(g[r][c])return false;
    for(int i=0;i<9;i++){ if(g[r][i]==d||g[i][c]==d)return false; }
    int br=r/3*3,bc=c/3*3;
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)if(g[br+i][bc+j]==d)return false;
    return true;
}
int main(){
    for(int i=0;i<9;i++)for(int j=0;j<9;j++)scanf("%d",&g[i][j]);
    // units
    vector<vector<pair<int,int>>> units;
    for(int i=0;i<9;i++){ vector<pair<int,int>> a,b,c; for(int j=0;j<9;j++){a.push_back({i,j});b.push_back({j,i});c.push_back({i/3*3+j/3,i%3*3+j%3});} units.push_back(a);units.push_back(b);units.push_back(c);}
    bool ch=true;
    while(ch){
        ch=false;
        for(int r=0;r<9;r++)for(int c=0;c<9;c++)if(!g[r][c]){
            int cnt=0,v=0; for(int d=1;d<=9;d++)if(can(r,c,d)){cnt++;v=d;}
            if(cnt==1){g[r][c]=v;ch=true;}
        }
        for(auto&u:units)for(int d=1;d<=9;d++){
            int cnt=0;pair<int,int> p;
            for(auto&q:u)if(can(q.first,q.second,d)){cnt++;p=q;}
            if(cnt==1){g[p.first][p.second]=d;ch=true;}
        }
    }
    bool full=true; for(int i=0;i<9;i++)for(int j=0;j<9;j++)if(!g[i][j])full=false;
    puts(full?"Easy":"Not easy");
    for(int i=0;i<9;i++){for(int j=0;j<9;j++){ if(j)putchar(' '); if(g[i][j])putchar('0'+g[i][j]); else putchar('.'); } putchar('\n');}
}
