#include <bits/stdc++.h>
using namespace std;
const long long MOD=998244353;
int t; unordered_map<long long,long long> memo;
long long f(long long n){
    if(n==0) return 1;
    auto it=memo.find(n); if(it!=memo.end()) return it->second;
    long long r=0;
    for(long long d=n&1; d<=t && d<=n; d+=2) r+=f((n-d)/2);
    r%=MOD; memo[n]=r; return r;
}
int main(){ long long n; cin>>n>>t; cout<<f(n)%MOD<<endl; }
