#include <bits/stdc++.h>
using namespace std;
int main(){
    long long xs,ys,xt,yt,xp,yp;
    cin>>xs>>ys>>xt>>yt>>xp>>yp;
    const long long B=1000000;
    // moving vertically away from the rock is always safe; outside the 1e4 box everything is free
    long long sy=(ys>=yp)?B:-B;
    long long ty=(yt>=yp)?B:-B;
    vector<pair<long long,long long>> p;
    p.push_back({xs,sy});
    if(sy!=ty){
        p.push_back({B,sy});
        p.push_back({B,ty});
    }
    p.push_back({xt,ty});
    printf("%d\n",(int)p.size());
    for(auto&q:p)printf("%lld %lld\n",q.first,q.second);
    fflush(stdout);
}
