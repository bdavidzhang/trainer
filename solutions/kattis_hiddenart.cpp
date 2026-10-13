#include <bits/stdc++.h>
using namespace std;
int main(){
    int h,w;
    if(scanf("%d %d",&h,&w)!=2) return 0;
    vector<string> g(h);
    char buf[64];
    auto id=[](char c){return c=='w'?0:c=='r'?1:c=='g'?2:3;};
    vector<vector<int>> a(h,vector<int>(w));
    for(int i=0;i<h;i++){scanf("%s",buf);for(int j=0;j<w;j++)a[i][j]=id(buf[j]);}
    int G=std::gcd(h,w);
    // comp[t] = mask of pair types (z,u) with {x,y,z,u} all distinct for t=(x,y)
    int comp[16];
    for(int x=0;x<4;x++)for(int y=0;y<4;y++){
        int m=0;
        if(x!=y) for(int z=0;z<4;z++)for(int u=0;u<4;u++) if(z!=u&&z!=x&&z!=y&&u!=x&&u!=y) m|=1<<(z*4+u);
        comp[x*4+y]=m;
    }
    vector<int> mask(G);
    for(int c=0;c<w;c++)for(int c2=0;c2<w;c2++){
        if(c==c2) continue;
        int b=((c2-c)%G+G)%G;
        fill(mask.begin(),mask.end(),0);
        int rr=0;
        for(int r=0;r<h;r++){
            mask[rr]|=1<<(a[r][c]*4+a[r][c2]);
            if(++rr==G) rr=0;
        }
        for(int p=0;p<G;p++){
            int q=(p+b)%G;
            int m1=mask[p],m2=mask[q];
            for(int t=0;t<16;t++) if((m1>>t&1)&&(comp[t]&m2)){puts("possible");return 0;}
        }
    }
    puts("impossible");
}
