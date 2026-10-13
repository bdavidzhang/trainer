#include <bits/stdc++.h>
using namespace std;
int main(){unsigned long long n;cin>>n;unsigned long long a=n,b=n+1,c=n+2;
if(a%2==0)a/=2;else b/=2;
if(a%3==0)a/=3;else if(b%3==0)b/=3;else c/=3;
const unsigned long long M=998244353;cout<<(a%M)*(b%M)%M*(c%M)%M<<endl;}
