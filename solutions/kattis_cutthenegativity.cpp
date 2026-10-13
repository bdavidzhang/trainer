#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n); vector<array<int,3>> r;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){int c;scanf("%d",&c); if(c!=-1) r.push_back({i,j,c});}
    printf("%d\n",(int)r.size());
    for(auto&x:r) printf("%d %d %d\n",x[0],x[1],x[2]);
}
