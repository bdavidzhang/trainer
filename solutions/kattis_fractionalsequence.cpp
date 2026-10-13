#include <bits/stdc++.h>
using namespace std;
int main(){long long n;cin>>n;long long i=(long long)((1+sqrtl(8.0L*n-7))/2);
while(i*(i-1)/2>=n)i--;while(i*(i+1)/2<n)i++;
long long k=n-i*(i-1)/2-1;if(k==0){cout<<i<<"\n";return 0;}
long long g=std::gcd(k,i);cout<<i<<" "<<k/g<<"/"<<i/g<<"\n";}
