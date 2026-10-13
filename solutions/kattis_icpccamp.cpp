#include <bits/stdc++.h>
using namespace std;
int n,p,q; long long s;
vector<long long> X,Y;
bool check(long long D){
    // classical x can pair with y in [x-D, min(x+D, s-x)]
    priority_queue<long long,vector<long long>,greater<long long>> pq;
    int i=0,cnt=0;
    for(long long y:Y){
        while(i<p && X[i]-D<=y){ pq.push(min(X[i]+D,s-X[i])); i++; }
        while(!pq.empty() && pq.top()<y) pq.pop();
        if(!pq.empty()){ pq.pop(); if(++cnt>=n) return true; }
    }
    return cnt>=n;
}
int main(){
    scanf("%d %d %d %lld",&n,&p,&q,&s);
    X.resize(p);Y.resize(q);
    for(auto&x:X)scanf("%lld",&x);
    for(auto&y:Y)scanf("%lld",&y);
    sort(X.begin(),X.end());sort(Y.begin(),Y.end());
    long long lo=0,hi=1000000000LL;
    if(!check(hi)){puts("-1");return 0;}
    while(lo<hi){long long mid=(lo+hi)/2; if(check(mid))hi=mid; else lo=mid+1;}
    printf("%lld\n",lo);
}
