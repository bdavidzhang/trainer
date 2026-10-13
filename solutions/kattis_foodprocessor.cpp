#include <bits/stdc++.h>
using namespace std;
int main(){
    int s,t,n;scanf("%d %d %d",&s,&t,&n);vector<pair<int,int>>b(n);
    for(auto&x:b)scanf("%d %d",&x.first,&x.second);
    sort(b.rbegin(),b.rend());
    double best=1e18,cur=s,cost=0;int i=0;
    while(i<n&&b[i].first>=s){best=min(best,(double)b[i].second);i++;}
    if(best>1e17){puts("-1");return 0;}
    for(;i<n;i++){
        if(b[i].first<=t)break;
        cost+=best*log2(cur/b[i].first);cur=b[i].first;best=min(best,(double)b[i].second);
    }
    cost+=best*log2(cur/t);
    printf("%.12g\n",cost);
}
