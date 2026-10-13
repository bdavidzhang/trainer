#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;scanf("%d",&n);
    map<pair<int,int>,int> c;
    for(int i=0;i<n;i++){
        int a,b,x,y;scanf("%d %d %d %d",&a,&b,&x,&y);
        c[{a,b}]^=1;c[{x,y}]^=1;
    }
    // dual graph is bipartite iff every vertex of the arrangement has even degree;
    // interior crossings add 2, so only the parity of endpoints at each point matters.
    for(auto&kv:c)if(kv.second){puts("yes");return 0;}
    puts("no");
}
