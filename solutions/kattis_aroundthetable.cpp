#include <bits/stdc++.h>
using namespace std;
int main(){long long l,r;cin>>l>>r;long long n=l+r;
 auto cnt=[&](long long d){return 2*d==n? n/2: n;};
 if(2*l-1==n)cout<<cnt(l)<<endl;else cout<<cnt(l)+cnt(l-1)<<endl;}
