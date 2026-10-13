#include <bits/stdc++.h>
using namespace std;
int n;
bool vis[2][500][500];
int main(){
    int mv[2][2];
    cin>>n>>mv[0][0]>>mv[0][1]>>mv[1][0]>>mv[1][1];
    // state t = type of the NEXT move to make
    queue<array<int,3>> q;
    for(int t=0;t<2;t++){vis[t][0][0]=true;q.push({t,0,0});}
    while(!q.empty()){
        auto [t,x,y]=q.front();q.pop();
        int a=mv[t][0],b=mv[t][1];
        int dx[8]={a,a,-a,-a,b,b,-b,-b},dy[8]={b,-b,b,-b,a,-a,a,-a};
        for(int k=0;k<8;k++){
            int nx=x+dx[k],ny=y+dy[k];
            if(nx<0||ny<0||nx>=n||ny>=n||vis[t^1][nx][ny])continue;
            vis[t^1][nx][ny]=true;q.push({t^1,nx,ny});
        }
    }
    int c=0;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(vis[0][i][j]||vis[1][i][j])c++;
    printf("%d\n",c);
}
