#include <bits/stdc++.h>
using namespace std;
// returns true if byte i is non-zero; exits on error responses
static bool readByte(long long i){
    printf("buf[%lld]\n",i); fflush(stdout);
    char line[128];
    if(scanf(" %127[^\n]",line)!=1) exit(0);
    if(!isdigit((unsigned char)line[0])) exit(0);
    return atoll(line)!=0;
}
int main(){
    // N>=2 so index 1 is non-zero. Double until a zero is seen: 2^k < N implies 2^(k+1) < 2N (safe).
    long long lo=1, hi=2;
    while(readByte(hi)){ lo=hi; hi*=2; }
    // buf[lo]!=0, buf[hi]==0, N = first zero index in (lo,hi]
    while(hi-lo>1){
        long long mid=lo+(hi-lo)/2;
        if(readByte(mid)) lo=mid; else hi=mid;
    }
    printf("strlen(buf) = %lld\n",hi); fflush(stdout);
}
