#include <bits/stdc++.h>
using namespace std;
int R,C; char g[55][55]; int dist_[51][51][52];
int main(){
    scanf("%d %d",&R,&C);
    int sr=0,sc=0;
    for(int i=0;i<R;i++){scanf("%s",g[i]);for(int j=0;j<C;j++) if(g[i][j]=='R'){sr=i;sc=j;}}
    char s[64]; scanf("%s",s); int L=strlen(s);
    const char* D="LURD"; int dr[4]={0,-1,0,1},dc[4]={-1,0,1,0};
    memset(dist_,0x3f,sizeof dist_);
    deque<array<int,3>> dq; dist_[sr][sc][0]=0; dq.push_back({sr,sc,0});
    auto mv=[&](int r,int c,int d,int&nr,int&nc){
        nr=r+dr[d];nc=c+dc[d];
        if(nr<0||nr>=R||nc<0||nc>=C||g[nr][nc]=='#'){nr=r;nc=c;}
    };
    while(!dq.empty()){
        auto [r,c,i]=dq.front();dq.pop_front();
        int d0=dist_[r][c][i];
        if(g[r][c]=='E'){printf("%d\n",d0);return 0;}
        auto relax=[&](int nr,int nc,int ni,int w){
            if(dist_[nr][nc][ni]>d0+w){dist_[nr][nc][ni]=d0+w; if(w) dq.push_back({nr,nc,ni}); else dq.push_front({nr,nc,ni});}
        };
        int nr,nc;
        if(i<L){
            int d=strchr(D,s[i])-D;
            mv(r,c,d,nr,nc); relax(nr,nc,i+1,0);
            relax(r,c,i+1,1);
        }
        for(int d=0;d<4;d++){mv(r,c,d,nr,nc); relax(nr,nc,i,1);}
    }
    return 0;
}
