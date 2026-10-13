#include <bits/stdc++.h>
using namespace std;
// Parking sequences with cars of different lengths (cyclic-shift argument):
// answer = z * prod_{i=1}^{n-1} (z + x_1+..+x_i + n - i), z = t + 1 - sum x.
int main(){
    const long long M=998244353;
    long long n,t; scanf("%lld %lld",&n,&t);
    vector<long long> x(n); long long S=0; for(auto&v:x){scanf("%lld",&v);S+=v;}
    long long z=t+1-S; long long ans=z%M, pre=0;
    for(long long i=1;i<n;i++){ pre+=x[i-1]; ans=ans*((z+pre+n-i)%M)%M; }
    printf("%lld\n",ans);
}
