#include <bits/stdc++.h>
using namespace std;
int main(){
    int r,c1,c2;
    cin>>r>>c1>>c2;
    vector<string> a(r),b(r);
    for(auto&s:a)cin>>s;
    for(auto&s:b)cin>>s;
    // combined width w; left occupies columns [0,c1), right occupies [w-c2,w).
    // Every column in [0,w) must hold exactly one 1; anything outside must be 0.
    for(int w=1;w<=c1+c2;w++){
        bool ok=true;
        int off=w-c2;
        int lo=min(0,off),hi=max(w,c1);
        for(int i=0;i<r&&ok;i++)for(int j=lo;j<hi;j++){
            int cnt=0;
            if(j>=0&&j<c1&&a[i][j]=='1')cnt++;
            if(j>=off&&j<w&&b[i][j-off]=='1')cnt++;
            int need=(j>=0&&j<w)?1:0;
            if(cnt!=need){ok=false;break;}
        }
        if(ok){puts("Yes");return 0;}
    }
    puts("No");
}
