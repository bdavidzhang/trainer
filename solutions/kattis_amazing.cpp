#include <bits/stdc++.h>
using namespace std;
const int S=420;
static bool vis[S][S];
const char* nm[4]={"up","right","down","left"};
int dx[4]={-1,0,1,0}, dy[4]={0,1,0,-1};
string ask(int d){
    printf("%s\n",nm[d]); fflush(stdout);
    char buf[64]; if(scanf("%63s",buf)!=1) exit(0);
    string r=buf;
    if(r=="solved"||r=="wrong") exit(0);
    return r;
}
int main(){
    // iterative DFS; never repeats a (cell, direction) move:
    // forward moves only go to unvisited cells, each back move happens once.
    vector<array<int,4>> st; // x,y,nextdir,parentdir(dir we came by)
    int sx=S/2, sy=S/2;
    vis[sx][sy]=true;
    st.push_back({sx,sy,0,-1});
    while(!st.empty()){
        auto &t=st.back();
        if(t[2]==4){
            int pd=t[3];
            st.pop_back();
            if(pd>=0) ask((pd+2)%4);
            continue;
        }
        int d=t[2]++;
        int nx=t[0]+dx[d], ny=t[1]+dy[d];
        if(vis[nx][ny]) continue;
        string r=ask(d);
        if(r=="ok"){
            vis[nx][ny]=true;
            st.push_back({nx,ny,0,d});
        }
    }
    printf("no way out\n"); fflush(stdout);
    char buf[64]; scanf("%63s",buf);
    return 0;
}
