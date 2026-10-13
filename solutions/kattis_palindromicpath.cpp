#include <bits/stdc++.h>
using namespace std;
#ifndef ND
#define ND 8
#endif
int R,C;vector<string> g;string s;int n;
vector<vector<char>> can;vector<char> vis;
int dr[8]={0,0,1,-1,1,1,-1,-1},dc[8]={1,-1,0,0,1,-1,1,-1};
long long budget;
bool dfs(int cell,int i){
    if(i==n-1)return true;
    if(--budget<0)return false;
    vis[cell]=1;
    int r=cell/C,c=cell%C;
    for(int d=0;d<ND;d++){int nr=r+dr[d],nc=c+dc[d];if(nr<0||nc<0||nr>=R||nc>=C)continue;int nb=nr*C+nc;
        if(vis[nb]||!can[i+1][nb])continue;
        if(dfs(nb,i+1)){vis[cell]=0;return true;}}
    vis[cell]=0;return false;
}
int main(){
    string line;getline(cin,line);sscanf(line.c_str(),"%d %d",&R,&C);
    g.resize(R);
    for(int i=0;i<R;i++){getline(cin,g[i]);while(!g[i].empty()&&(g[i].back()=='\r'||g[i].back()=='\n'))g[i].pop_back();g[i].resize(C,' ');}
    getline(cin,line);int p=atoi(line.c_str());
    for(int q=1;q<=p;q++){
        getline(cin,s);while(!s.empty()&&(s.back()=='\r'||s.back()=='\n'))s.pop_back();
        n=s.size();bool ok=false;
        if(n==0)ok=true;
        else if(n<=R*C){
            can.assign(n,vector<char>(R*C,0));
            for(int i=n-1;i>=0;i--)for(int r=0;r<R;r++)for(int c=0;c<C;c++){
                if(g[r][c]!=s[i])continue;
                if(i==n-1){can[i][r*C+c]=1;continue;}
                for(int d=0;d<ND;d++){int nr=r+dr[d],nc=c+dc[d];if(nr<0||nc<0||nr>=R||nc>=C)continue;
                    if(can[i+1][nr*C+nc]){can[i][r*C+c]=1;break;}}
            }
            vis.assign(R*C,0);
            budget=3000000;
            for(int cell=0;cell<R*C&&!ok;cell++)if(can[0][cell])ok=dfs(cell,0);
        }
        printf("Case %d: %s    %s\n",q,ok?"Yes":"No",s.c_str());
    }
}
