#include <bits/stdc++.h>
using namespace std;
int main(){
    vector<string> g(7);
    for(auto&s:g)cin>>s;
    int d,h;cin>>d>>h;
    double best=0;
    for(int m=1;m<128;m++){
        int pc=__builtin_popcount(m);
        if(pc<d)continue;
        vector<int> c(24,0);
        for(int i=0;i<7;i++)if(m>>i&1)for(int j=0;j<24;j++)if(g[i][j]=='.')c[j]++;
        sort(c.rbegin(),c.rend());
        int s=0;
        for(int j=0;j<h;j++)s+=c[j];
        best=max(best,(double)s/(pc*h));
    }
    printf("%.12f\n",best);
}
