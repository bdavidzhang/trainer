#include <bits/stdc++.h>
using namespace std;
int main(){long long n;cin>>n;
 if(n<=50){long double best=-1;long long bk=1;const long double PI=acosl(-1.0L);
  for(long long k=1;k<n;k++){long long g=std::gcd(n,k);long double v=(long double)(n/g)*sinl(PI*k/n);if(v>best+1e-12L){best=v;bk=k;}}
  cout<<bk<<endl;return 0;}
 long long k; if(n%2==1)k=(n-1)/2; else if(n%4==0)k=n/2-1; else k=n/2-2;
 cout<<k<<endl;}
