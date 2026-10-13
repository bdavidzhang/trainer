#include <bits/stdc++.h>
using namespace std;
// Ski rental. If a<=c never buy. Otherwise fly the airline k times and buy on flight k+1,
// with k the smallest value such that (k+2)*a >= b+c.
int main(){
    long long a,b,c;
    if(scanf("%lld %lld %lld",&a,&b,&c)!=3) return 0;
    long long k=-1; // -1 => never buy
    if(a>c){
        k=(b+c+a-1)/a-2;
        if(k<0) k=0;
    }
    long long cnt=0; bool bought=false;
    char s[32];
    while(scanf("%31s",s)==1){
        if(s[0]=='e') break;
        if(bought) puts("self");
        else if(k>=0 && cnt>=k){ puts("buy"); bought=true; }
        else puts("airline");
        fflush(stdout);
        cnt++;
    }
    return 0;
}
