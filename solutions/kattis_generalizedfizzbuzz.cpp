#include <bits/stdc++.h>
using namespace std;
int main(){ long long n,a,b; cin>>n>>a>>b; long long l=a/std::gcd(a,b)*b; long long fb=n/l; cout<<n/a-fb<<" "<<n/b-fb<<" "<<fb<<endl; }
