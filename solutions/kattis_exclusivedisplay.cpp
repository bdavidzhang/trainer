#include <bits/stdc++.h>
using namespace std;
int main(){
    vector<string> g(7);
    for(auto&s:g)cin>>s;
    // bits: a=1,b=2,c=4,d=8,e=16,f=32,g=64
    int st=0;
    if(g[0][1]=='#')st|=1;
    if(g[1][3]=='#')st|=2;
    if(g[4][3]=='#')st|=4;
    if(g[6][1]=='#')st|=8;
    if(g[4][0]=='#')st|=16;
    if(g[1][0]=='#')st|=32;
    if(g[3][1]=='#')st|=64;
    int d[10]={1|2|4|8|16|32, 2|4, 1|2|8|16|64, 1|2|4|8|64, 2|4|32|64, 1|4|8|32|64, 1|4|8|16|32|64, 1|2|4, 127, 1|2|4|8|32|64};
    vector<int> r;
    for(int s=0;s<100;s++){
        int m = s<10? d[s] : (d[s/10]^d[s%10]);
        if(m==st) r.push_back(s);
    }
    if(r.empty()){puts("impossible");return 0;}
    for(size_t i=0;i<r.size();i++)printf("%d%c",r[i],i+1==r.size()?'\n':' ');
}
