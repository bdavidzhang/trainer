#include <bits/stdc++.h>
using namespace std;
int R,C; vector<string> g;
int dr[4]={-1,0,1,0},dc[4]={0,1,0,-1};
bool loopc(int r,int c){return r>=0&&r<R&&c>=0&&c<C&&g[r][c]!='.';}
// ve[r][c]=1 if the loop has an edge between (r,c) and (r+1,c)
vector<vector<char>> trace(char ch){
    vector<vector<char>> ve(R,vector<char>(C,0));
    int sr=-1,sc=-1;
    for(int i=0;i<R;i++)for(int j=0;j<C;j++)if(g[i][j]==ch){sr=i;sc=j;}
    int d=-1;
    for(int k=0;k<4;k++)if(loopc(sr+dr[k],sc+dc[k])){d=k;break;}
    int r=sr,c=sc;
    do{
        int nr=r+dr[d],nc=c+dc[d];
        if(d==2)ve[r][c]=1; else if(d==0)ve[nr][nc]=1;
        r=nr;c=nc;
        if(r==sr&&c==sc)break;
        int cnt=0;
        for(int k=0;k<4;k++)if(loopc(r+dr[k],c+dc[k]))cnt++;
        if(cnt<4){
            for(int k=0;k<4;k++){
                if(k==(d+2)%4)continue;
                if(loopc(r+dr[k],c+dc[k])){d=k;break;}
            }
        }
    }while(true);
    return ve;
}
int main(){
    cin>>R>>C; g.resize(R); for(auto&s:g)cin>>s;
    auto ea=trace('A'),eb=trace('B');
    long long a=0,b=0,ab=0;
    for(int r=0;r<R;r++){
        int pa=0,pb=0;
        for(int c=0;c<C;c++){
            if(g[r][c]=='.'){
                if(pa&&pb)ab++; else if(pa)a++; else if(pb)b++;
            }
            pa^=ea[r][c]; pb^=eb[r][c];
        }
    }
    cout<<a<<" "<<b<<" "<<ab<<"\n";
}
