#include <bits/stdc++.h>
using namespace std;
int main(){
    int m,n;scanf("%d %d",&m,&n);
    vector<vector<int>> g(m,vector<int>(n));
    for(auto&r:g)for(auto&x:r)scanf("%d",&x);
    int r,c;scanf("%d %d",&r,&c);r--;c--;
    int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
    vector<int> path;long long steps=0;
    while(g[r][c]!=-1){
        if(g[r][c]==-2||++steps>(long long)m*n+5){puts("impossible");return 0;}
        int k=-1;
        for(int d=0;d<4;d++){int a=r+dx[d],b=c+dy[d];if(a>=0&&a<m&&b>=0&&b<n&&g[a][b]==g[r][c])k=d;}
        path.push_back(g[r][c]);
        r+=2*dx[k];c+=2*dy[k];
        if(r<0||r>=m||c<0||c>=n){puts("impossible");return 0;}
    }
    for(int i=(int)path.size()-1;i>=0;i--)printf("%d%c",path[i],i?' ':'\n');
}
