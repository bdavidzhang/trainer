#include <bits/stdc++.h>
using namespace std;
const int OFF=450, SZ=1000;
static int grid[SZ][SZ]; // scooter id or -1
int n,rx,ry,tx,ty;
vector<int> sx,sy; vector<bool> alive;
vector<int> moves; // 0 up 1 down 2 left 3 right
const int DX[4]={0,0,-1,1}, DY[4]={1,-1,0,0};
const char* NAME[4]={"up","down","left","right"};
void mv(int d){
    int nx=rx+DX[d], ny=ry+DY[d];
    if(grid[nx][ny]>=0){
        int qx=nx,qy=ny;
        while(grid[qx][qy]>=0){qx+=DX[d];qy+=DY[d];}
        // shift chain from the far end
        while(qx!=nx||qy!=ny){
            int px=qx-DX[d],py=qy-DY[d];
            int id=grid[px][py]; grid[px][py]=-1;
            if(qx==tx&&qy==ty) alive[id]=false;
            else { grid[qx][qy]=id; sx[id]=qx; sy[id]=qy; }
            qx=px;qy=py;
        }
    }
    rx=nx;ry=ny; moves.push_back(d);
}
static int distv[SZ][SZ], stamp[SZ][SZ], curStamp=0; static signed char from[SZ][SZ];
bool walkTo(int gx,int gy){
    int lox=min(min(rx,tx),gx),hix=max(max(rx,tx),gx),loy=min(min(ry,ty),gy),hiy=max(max(ry,ty),gy);
    for(int i=0;i<n;i++) if(alive[i]){lox=min(lox,sx[i]);hix=max(hix,sx[i]);loy=min(loy,sy[i]);hiy=max(hiy,sy[i]);}
    lox-=2;hix+=2;loy-=2;hiy+=2;
    curStamp++;
    deque<pair<int,int>> dq; dq.push_back({rx,ry}); stamp[rx][ry]=curStamp; from[rx][ry]=-1;
    bool found=false;
    while(!dq.empty()){
        auto [x,y]=dq.front(); dq.pop_front();
        if(x==gx&&y==gy){found=true;break;}
        for(int d=0;d<4;d++){
            int ax=x+DX[d],ay=y+DY[d];
            if(ax<lox||ax>hix||ay<loy||ay>hiy) continue;
            if(stamp[ax][ay]==curStamp||grid[ax][ay]>=0) continue;
            stamp[ax][ay]=curStamp; from[ax][ay]=d; dq.push_back({ax,ay});
        }
    }
    if(!found) return false;
    vector<int> path; int x=gx,y=gy;
    while(from[x][y]>=0){int d=from[x][y]; path.push_back(d); x-=DX[d]; y-=DY[d];}
    reverse(path.begin(),path.end());
    for(int d:path) mv(d);
    return true;
}
bool tryRemove(int s){
    while(alive[s]){
        int d; bool hor=sx[s]!=tx;
        if(hor) d=(tx>sx[s])?3:2; else d=(ty>sy[s])?0:1;
        int qx=sx[s]-DX[d],qy=sy[s]-DY[d];
        while(grid[qx][qy]>=0){qx-=DX[d];qy-=DY[d];}
        if(!walkTo(qx,qy)) return false;
        while(alive[s]&&(!hor||sx[s]!=tx)) mv(d);
    }
    return true;
}
int main(){
    scanf("%d",&n);
    scanf("%d %d %d %d",&rx,&ry,&tx,&ty);
    rx+=OFF;ry+=OFF;tx+=OFF;ty+=OFF;
    memset(grid,-1,sizeof grid);
    sx.resize(n);sy.resize(n);alive.assign(n,true);
    for(int i=0;i<n;i++){scanf("%d %d",&sx[i],&sy[i]);sx[i]+=OFF;sy[i]+=OFF;grid[sx[i]][sy[i]]=i;}
    mt19937 rnd(12345);
    while(true){
        bool any=false,prog=false;
        // prefer scooters already in the depot column
        vector<int> order;
        for(int i=0;i<n;i++) if(alive[i]&&sx[i]==tx) order.push_back(i);
        for(int i=0;i<n;i++) if(alive[i]&&sx[i]!=tx) order.push_back(i);
        for(int i:order){ any=true; if(!alive[i]) continue; if(tryRemove(i)){prog=true;break;} if(!alive[i]){prog=true;break;} }
        if(!any) break;
        if(!prog) mv(rnd()%4);
    }
    string out;
    for(int d:moves){out+=NAME[d];out+='\n';}
    fputs(out.c_str(),stdout);
}
