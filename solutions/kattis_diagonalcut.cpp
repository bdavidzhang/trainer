#include <bits/stdc++.h>
using namespace std;
int main(){long long m,n;cin>>m>>n;long long g=std::gcd(m,n);
 if(((m/g)&1)&&((n/g)&1))cout<<g<<"\n";else cout<<0<<"\n";}
