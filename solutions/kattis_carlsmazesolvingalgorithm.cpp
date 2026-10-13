#include <bits/stdc++.h>
using namespace std;
int main(){int r,c,si,sj,ei,ej;cin>>r>>c>>si>>sj>>ei>>ej;vector<string>g(r);for(auto&s:g)cin>>s;
    si--;sj--;ei--;ej--;
    // dirs clockwise: right, down, left, up ; left turn = (d+3)%4
    int di[4]={0,1,0,-1},dj[4]={1,0,-1,0};
    auto ok=[&](int i,int j){return i>=0&&i<r&&j>=0&&j<c&&g[i][j]=='0';};
    int i=si,j=sj,d=0;
    vector<char> vis(r*c*4,0);
    while(true){
        if(i==ei&&j==ej){puts("1");return 0;}
        int id=(i*c+j)*4+d;if(vis[id]){puts("0");return 0;}vis[id]=1;
        int l=(d+3)%4;
        if(ok(i+di[l],j+dj[l])){d=l;i+=di[d];j+=dj[d];}
        else if(ok(i+di[d],j+dj[d])){i+=di[d];j+=dj[d];}
        else d=(d+1)%4;
    }
}
