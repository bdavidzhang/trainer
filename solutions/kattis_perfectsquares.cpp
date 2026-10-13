#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> primes;
static bool sum2(ll r){
    if(r==0) return true;
    for(int p:primes){
        if((ll)p*p>r) break;
        if(r%p==0){ int e=0; while(r%p==0){r/=p;e++;} if((p&3)==3&&(e&1)) return false; }
    }
    if(r>1&&(r&3)==3) return false;
    return true;
}
int main(){
    ll n; scanf("%lld",&n);
    ll mul=1; ll m=n;
    while(m%4==0){m/=4;mul*=2;}
    if(m%8==7){puts("-1");return 0;}
    const int LIM=1000001;
    vector<char> comp(LIM+1,0);
    for(int i=2;i<=LIM;i++){ if(!comp[i]){primes.push_back(i); for(ll j=(ll)i*i;j<=LIM;j+=i) comp[j]=1;} }
    for(ll z=0;z*z<=m;z++){
        ll r=m-z*z;
        if(!sum2(r)) continue;
        ll y=(ll)sqrtl((long double)r); while(y*y>r) y--; while((y+1)*(y+1)<=r) y++;
        for(ll x=0;x<=y;x++){
            while(y>=x && x*x+y*y>r) y--;
            if(y<x) break;
            if(x*x+y*y==r){ printf("%lld %lld %lld\n",x*mul,y*mul,z*mul); return 0; }
        }
    }
    puts("-1");
}
