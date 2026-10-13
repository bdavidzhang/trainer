#include <bits/stdc++.h>
using namespace std;
int main(){
    int X,Y; string key; cin>>X>>Y>>key; vector<string> g(Y); for(int i=Y-1;i>=0;i--)cin>>g[i];
    int K=key.size(); const int INF=1e9;
    vector<vector<vector<int>>> dp(Y,vector<vector<int>>(X,vector<int>(K+1,INF)));
    dp[0][0][0]=g[0][0]-'0'; int best=INF;
    for(int y=0;y<Y;y++)for(int x=0;x<X;x++)for(int j=0;j<=K;j++){
        int v=dp[y][x][j]; if(v>=INF)continue;
        if(y==Y-1&&x==X-1)best=min(best,v);
        auto rel=[&](int ny,int nx,int nj){ if(ny<Y&&nx<X){int&t=dp[ny][nx][nj]; t=min(t,v+g[ny][nx]-'0');} };
        rel(y+1,x,j); rel(y,x+1,j);
        if(j<K){int d=key[j]-'0'+1; rel(y+d,x,j+1); rel(y,x+d,j+1);}
    }
    printf("%d\n",best);
}
