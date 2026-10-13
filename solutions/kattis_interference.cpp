#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; long long w; scanf("%d %lld",&n,&w);
    vector<array<long long,3>> ws;
    while(n--){
        char op[4]; scanf("%3s",op);
        if(op[0]=='!'){ long long p,l,a; scanf("%lld %lld %lld",&p,&l,&a); ws.push_back({p,l,a}); }
        else { long long p; scanf("%lld",&p); long long r=0;
            for(auto&x:ws) if(p>=x[0]&&p<x[0]+x[1]){ int d=(p-x[0])%4; if(d==0)r+=x[2]; else if(d==2)r-=x[2]; }
            printf("%lld\n",r); }
    }
}
