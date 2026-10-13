#include <bits/stdc++.h>
using namespace std;
int R,Cn;
int val[20][20];      // 0 = empty
char bon[20][20];     // bonus char for empty cells
bool isnew[20][20];
int t; int tiles[10];
bool inb(int r,int c){return r>=0&&r<R&&c>=0&&c<Cn;}
// score the maximal run through (r,c) along (dr,dc). returns -1 invalid, 0 if length 1, else score
long long seqScore(int r,int c,int dr,int dc){
    int sr=r,sc=c;
    while(inb(sr-dr,sc-dc)&&val[sr-dr][sc-dc])sr-=dr,sc-=dc;
    int len=0;long long sum=0,mul=1;bool inc=true,dec=true;int prev=-1;
    for(int x=sr,y=sc;inb(x,y)&&val[x][y];x+=dr,y+=dc){
        int v=val[x][y];
        if(prev>=0){if(v<prev)inc=false;if(v>prev)dec=false;}
        prev=v;len++;
        if(isnew[x][y]){
            char b=bon[x][y];
            if(b=='d')v*=2;else if(b=='t')v*=3;else if(b=='D')mul*=2;else if(b=='T')mul*=3;
        }
        sum+=v;
    }
    if(len<2)return 0;
    if(!inc&&!dec)return -1;
    sum*=mul;
    if(sum%3)return -1;
    return sum;
}
int main(){
    scanf("%d %d",&R,&Cn);
    for(int i=0;i<R;i++)for(int j=0;j<Cn;j++){char s[8];scanf("%s",s);if(isdigit(s[0]))val[i][j]=s[0]-'0';else bon[i][j]=s[0];}
    scanf("%d",&t);for(int i=0;i<t;i++)scanf("%d",&tiles[i]);
    sort(tiles,tiles+t);
    // canonical masks (for equal tiles take the earliest ones), grouped by popcount
    vector<vector<int>> byPop(t+1);
    for(int m=1;m<(1<<t);m++){
        bool ok=true;
        for(int i=1;i<t;i++)if((m>>i&1)&&!(m>>(i-1)&1)&&tiles[i]==tiles[i-1])ok=false;
        if(ok)byPop[__builtin_popcount(m)].push_back(m);
    }
    long long best=0;
    const int DR[2]={0,1},DC[2]={1,0};
    for(int o=0;o<2;o++){
        int dr=DR[o],dc=DC[o];
        for(int r=0;r<R;r++)for(int c=0;c<Cn;c++){
            if(val[r][c])continue;
            // consecutive empty cells along the line starting here (skipping existing tiles)
            vector<pair<int,int>> cells;
            for(int x=r,y=c;inb(x,y)&&(int)cells.size()<t;x+=dr,y+=dc)if(!val[x][y])cells.push_back({x,y});
            for(int j=1;j<=(int)cells.size();j++){
                // connectivity: some placed cell must be adjacent to an existing tile
                bool conn=false;
                for(int i=0;i<j&&!conn;i++){
                    int x=cells[i].first,y=cells[i].second;
                    static const int ar[4]={0,0,1,-1},ac[4]={1,-1,0,0};
                    for(int d=0;d<4;d++){int nx=x+ar[d],ny=y+ac[d];if(inb(nx,ny)&&val[nx][ny])conn=true;}
                }
                // cells must form a gap-free line: between consecutive placed cells only tiles (true by construction)
                if(!conn)continue;
                for(int m:byPop[j]){
                    int sel[10],k=0;
                    for(int i=0;i<t;i++)if(m>>i&1)sel[k++]=tiles[i];
                    for(int dir=0;dir<2;dir++){
                        if(dir==1&&sel[0]==sel[j-1])break;
                        for(int i=0;i<j;i++){int v=dir?sel[j-1-i]:sel[i];val[cells[i].first][cells[i].second]=v;isnew[cells[i].first][cells[i].second]=true;}
                        long long tot=0;bool ok=true;
                        long long s=seqScore(r,c,dr,dc);
                        if(s<0)ok=false;else tot+=s;
                        for(int i=0;i<j&&ok;i++){
                            s=seqScore(cells[i].first,cells[i].second,dc,dr);
                            if(s<0)ok=false;else tot+=s;
                        }
                        if(ok&&tot>best)best=tot;
                        for(int i=0;i<j;i++){val[cells[i].first][cells[i].second]=0;isnew[cells[i].first][cells[i].second]=false;}
                    }
                }
            }
        }
    }
    printf("%lld\n",best);
}
