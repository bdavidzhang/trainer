#include <bits/stdc++.h>
using namespace std;
int main(){
    long long n; scanf("%lld",&n);
    long long g=1; while(g*g*g<n) g++;
    if(g<2) g=2;
    vector<pair<int,int>> out;
    long long u=1;
    for(int lev=0; lev<3 && u<n; lev++){
        long long big=u*g;
        for(long long j=1;j<g;j++){
            // positions y<n with y mod big == j*u, descending
            long long r=j*u;
            if(r>=n) break;
            long long top=(n-1-r)/big*big+r;
            for(long long y=top;y>=1;y-=big) out.push_back({(int)y,(int)u});
        }
        u=big;
    }
    printf("%d\n",(int)out.size());
    for(auto&p:out) printf("%d %d\n",p.first,p.second);
}
