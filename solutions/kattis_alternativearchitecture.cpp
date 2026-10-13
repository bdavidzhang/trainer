#include <bits/stdc++.h>
using namespace std;
int main(){
    long long a,b; scanf("%lld %lld",&a,&b); a--; b--;
    long long g=std::gcd(a,b);
    // lattice points (x,y) with x>0,y>=0 on circle of radius g
    long long cnt=0;
    for(long long x=1;x<=g;x++){
        long long r=g*g-x*x; long long y=(long long)sqrtl((long double)r);
        while(y*y>r) y--; while((y+1)*(y+1)<=r) y++;
        if(y*y==r) cnt++;
    }
    printf("%lld\n", a==b?cnt:2*cnt);
}
