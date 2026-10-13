#include <bits/stdc++.h>
using namespace std;
int main(){
    // Query t = 1,2,4,...,2^40. While answer == t, lap length L > t.
    // First time answer x != t we have L <= t < 2L, hence L = t - x.
    for(int k=0;k<=40;k++){
        long long t=1LL<<k;
        printf("? %lld\n",t);fflush(stdout);
        long long x; if(scanf("%lld",&x)!=1) return 0;
        if(x!=t){ printf("! %lld\n",t-x);fflush(stdout);return 0; }
    }
    return 0;
}
