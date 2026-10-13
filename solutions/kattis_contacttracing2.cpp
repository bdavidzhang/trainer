#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k,c; scanf("%d %d %d",&n,&k,&c);
    vector<array<int,3>> e(c); vector<int> last(n+1,0);
    for(auto&x:e){scanf("%d %d %d",&x[0],&x[1],&x[2]); last[x[0]]=max(last[x[0]],x[2]); last[x[1]]=max(last[x[1]],x[2]);}
    vector<char> cur(n+1,0),nx;
    for(int v=1;v<=n;v++)cur[v]=last[v]<=1;
    for(int d=1;d<=k;d++){
        nx.assign(n+1,0);
        for(auto&x:e)if(x[2]==d){
            if(cur[x[0]]&&last[x[1]]<=d+1)nx[x[1]]=1;
            if(cur[x[1]]&&last[x[0]]<=d+1)nx[x[0]]=1;
        }
        cur=nx;
    }
    vector<int> r; for(int v=1;v<=n;v++)if(cur[v])r.push_back(v);
    printf("%d\n",(int)r.size()); for(int v:r)printf("%d\n",v);
}
