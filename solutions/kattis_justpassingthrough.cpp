#include <bits/stdc++.h>
using namespace std;
int g[502][502]; bool ps[502][502];
int main(){
    int r,c,n; scanf("%d %d %d",&r,&c,&n);
    for(int i=0;i<r;i++)for(int j=0;j<c;j++)scanf("%d",&g[i][j]);
    for(int i=1;i+1<r;i++)for(int j=1;j+1<c;j++){
        int v=g[i][j];
        if(v<0||g[i-1][j]<0||g[i+1][j]<0||g[i][j-1]<0||g[i][j+1]<0)continue;
        if(g[i][j-1]<v&&g[i][j+1]<v&&g[i-1][j]>v&&g[i+1][j]>v)ps[i][j]=true;
    }
    const int INF=1e9;
    vector<array<int,11>> cur(r),nx(r);
    for(int i=0;i<r;i++){cur[i].fill(INF); if(g[i][0]>=0)cur[i][0]=g[i][0];}
    for(int j=1;j<c;j++){
        for(int i=0;i<r;i++){
            nx[i].fill(INF);
            if(g[i][j]<0)continue;
            int sh=ps[i][j]?1:0;
            for(int d=-1;d<=1;d++){
                int p=i+d; if(p<0||p>=r)continue;
                for(int k=0;k+sh<=n;k++) if(cur[p][k]<INF)
                    nx[i][k+sh]=min(nx[i][k+sh],cur[p][k]+g[i][j]);
            }
        }
        swap(cur,nx);
    }
    int ans=INF;
    for(int i=0;i<r;i++)ans=min(ans,cur[i][n]);
    if(ans>=INF)puts("impossible"); else printf("%d\n",ans);
}
