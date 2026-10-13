#include <bits/stdc++.h>
using namespace std;
// The grid must be exactly the complement of the (rotated) block inside its bounding box
// (plus fully filled padding columns). The block can drop in iff in every column its cells
// form a run starting at the top row. Try the 4 rotations.
int main(){
    int h,w; cin>>h>>w;
    vector<string> g(h);
    for(auto&s:g) cin>>s;
    for(int rot=0;rot<4;rot++){
        int H=g.size(), W=g[0].size();
        bool good=true;
        for(int c=0;c<W&&good;c++){
            bool seenEmpty=false;
            for(int r=0;r<H;r++){
                if(g[r][c]=='.') seenEmpty=true;
                else if(seenEmpty){ good=false; break; }
            }
        }
        if(good){
            printf("%d %d\n",H,W+1);
            for(int r=0;r<H;r++){
                string s(W+1,'#');
                for(int c=0;c<W;c++) s[c]=(g[r][c]=='#'?'.':'#');
                puts(s.c_str());
            }
            return 0;
        }
        vector<string> ng(W,string(H,'.'));
        for(int r=0;r<H;r++)for(int c=0;c<W;c++) ng[c][H-1-r]=g[r][c];
        g=ng;
    }
    puts("impossible");
}
