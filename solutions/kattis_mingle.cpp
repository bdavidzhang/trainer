#include <bits/stdc++.h>
using namespace std;
const long long M=998244353;
long long pw(long long b,long long e){long long r=1;b%=M;while(e){if(e&1)r=r*b%M;b=b*b%M;e>>=1;}return r;}
int main(){long long n,k;cin>>n>>k;
    // each player wins w.p. sum over rooms 1/(2k+1) * (2k/(2k+1))^(2k) = (2k/(2k+1))^(2k)
    long long q=2*k%M*pw(2*k+1,M-2)%M;
    cout<<n%M*pw(q,2*k)%M<<endl;}
