#include <bits/stdc++.h>
using namespace std;
// Directions in alphabetical order: E, N, S, W
static const int DR[4]={0,-1,1,0}, DC[4]={1,0,0,-1};
static const char DN[5]="ENSW";
int k,n,m,sr,sc; string s;
int req[64]; // 0 free, 1 straight, 2 turn
int d[64]; bool vis[52][52];
// reach[d0][i][prev]: displacements (dr,dc) realisable by moves i..k-1 when move i-1 was prev,
// honouring the static straight/turn requirement of every cell (ignores self-avoidance and borders)
const int OFF=61, W=123;
static bitset<W*W> reach[4][62][4];
void buildReach(){
    for(int d0=0;d0<4;d0++){
        for(int pv=0;pv<4;pv++){
            reach[d0][k][pv].reset();
            bool okc=!(req[0]==1&&pv!=d0)&&!(req[0]==2&&pv==d0)&&pv!=3-d0;
            if(okc)reach[d0][k][pv].set(OFF*W+OFF);
        }
        for(int i=k-1;i>=1;i--)for(int pv=0;pv<4;pv++){
            bitset<W*W> acc;
            for(int dir=0;dir<4;dir++){
                if(dir==3-pv)continue;
                if(req[i]==1&&dir!=pv)continue;
                if(req[i]==2&&dir==pv)continue;
                int sh=DR[dir]*W+DC[dir];
                if(sh>0)acc|=reach[d0][i+1][dir]<<sh; else acc|=reach[d0][i+1][dir]>>(-sh);
            }
            reach[d0][i][pv]=acc;
        }
    }
}
bool whiteOK(int j){ // all moves known
    int a=d[((j-2)%k+k)%k], b=d[((j-1)%k+k)%k], c=d[j], e=d[(j+1)%k];
    if(b!=c) return false;
    return a!=b || c!=e;
}
bool rec(int i,int r,int c){
    if(i==k){
        if(req[0]==1&&d[k-1]!=d[0])return false;
        if(req[0]==2&&d[k-1]==d[0])return false;
        int chk[3]={0,1,k-1};
        for(int j:chk) if(s[j]=='W'&&!whiteOK(j))return false;
        return true;
    }
    for(int dir=0;dir<4;dir++){
        if(i>=1){
            if(dir==3-d[i-1])continue;
            if(req[i]==1&&dir!=d[i-1])continue;
            if(req[i]==2&&dir==d[i-1])continue;
            if(i>=3&&s[i-1]=='W'&&d[i-3]==d[i-2]&&d[i-1]==dir)continue;
        }
        int nr=r+DR[dir],nc=c+DC[dir];
        if(nr<1||nr>n||nc<1||nc>m)continue;
        int rem=k-(i+1);
        if(rem==0){ if(nr!=sr||nc!=sc)continue; }
        else {
            if(vis[nr][nc])continue;
            if(abs(nr-sr)+abs(nc-sc)>rem)continue;
        }
        {
            int d0=(i==0)?dir:d[0];
            if(!reach[d0][i+1][dir].test((sr-nr+OFF)*W+(sc-nc+OFF)))continue;
        }
        d[i]=dir;
        if(rem>0)vis[nr][nc]=true;
        if(rec(i+1,nr,nc))return true;
        if(rem>0)vis[nr][nc]=false;
    }
    return false;
}
int main(){
    cin>>k>>n>>m>>s>>sr>>sc;
    bool ok=(k%2==0);
    for(int i=0;i<k&&ok;i++){
        int want=0;
        if(s[i]=='B')want=2;
        else if(s[i]=='W')want=1;
        if(s[(i+1)%k]=='B'||s[(i+k-1)%k]=='B'){ if(want==2)ok=false; want=1; }
        req[i]=want;
    }
    if(ok){ buildReach(); vis[sr][sc]=true; ok=rec(0,sr,sc); }
    if(!ok){puts("impossible");return 0;}
    string out; for(int i=0;i<k;i++)out+=DN[d[i]];
    puts(out.c_str());
}
