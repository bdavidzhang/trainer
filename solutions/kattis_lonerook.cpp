#include <bits/stdc++.h>
using namespace std;
int R,C;char g[755][755];int att[755][755];bool vis[2][755][755],reached[755][755];
vector<pair<int,int>> q;
const int kx[8]={1,1,-1,-1,2,2,-2,-2},ky[8]={2,-2,2,-2,1,-1,1,-1};
void tryReach(int i,int j){if(!reached[i][j]&&att[i][j]==0&&(vis[0][i][j]||vis[1][i][j])){reached[i][j]=1;q.push_back({i,j});}}
int main(){scanf("%d %d",&R,&C);int si=0,sj=0,ti=0,tj=0;for(int i=0;i<R;i++){scanf("%s",g[i]);for(int j=0;j<C;j++){if(g[i][j]=='R'){si=i;sj=j;}if(g[i][j]=='T'){ti=i;tj=j;}}}
    for(int i=0;i<R;i++)for(int j=0;j<C;j++)if(g[i][j]=='K')for(int d=0;d<8;d++){int a=i+kx[d],b=j+ky[d];if(a>=0&&b>=0&&a<R&&b<C)att[a][b]++;}
    reached[si][sj]=1;q.push_back({si,sj});
    for(size_t h=0;h<q.size();h++){int i=q[h].first,j=q[h].second;
        bool wasK=g[i][j]=='K';
        if(wasK){g[i][j]='.';for(int d=0;d<8;d++){int a=i+kx[d],b=j+ky[d];if(a>=0&&b>=0&&a<R&&b<C){att[a][b]--;tryReach(a,b);}}}
        for(int ax=0;ax<2;ax++){if(vis[ax][i][j]&&!wasK)continue;vis[ax][i][j]=1;
            for(int s=-1;s<=1;s+=2){int a=i,b=j;while(true){if(ax==0)b+=s;else a+=s;if(a<0||b<0||a>=R||b>=C)break;
                if(vis[ax][a][b])break;vis[ax][a][b]=1;tryReach(a,b);if(g[a][b]=='K')break;}}}
    }
    puts(reached[ti][tj]?"yes":"no");
}
