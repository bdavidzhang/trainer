#include <bits/stdc++.h>
using namespace std;
int n,k,sunk=0;
bool shot[101][101];
// returns 0 miss, 1 hit, 2 sunk
int fire(int x,int y){
    if(x<1||y<1||x>n||y>n||shot[x][y])return 0;
    shot[x][y]=true;
    printf("%d %d\n",x,y);fflush(stdout);
    char buf[16];
    if(scanf("%15s",buf)!=1)exit(0);
    if(buf[0]=='h')return 1;
    if(buf[0]=='s'){if(++sunk==k)exit(0);return 2;}
    return 0;
}
int main(){
    scanf("%d %d",&n,&k);
    int bc=0,bcnt=INT_MAX;
    for(int c=0;c<5;c++){
        int cnt=0;
        for(int x=1;x<=n;x++)for(int y=1;y<=n;y++)if((x+2*y)%5==c)cnt++;
        if(cnt<bcnt){bcnt=cnt;bc=c;}
    }
    for(int x=1;x<=n;x++)for(int y=1;y<=n;y++)if((x+2*y)%5==bc){
        if(fire(x,y)){
            for(int d=1;d<=4;d++){fire(x+d,y);fire(x-d,y);fire(x,y+d);fire(x,y-d);}
        }
    }
}
