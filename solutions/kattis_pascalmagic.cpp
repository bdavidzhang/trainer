#include <bits/stdc++.h>
using namespace std;
int main(){unsigned long long n,p;cin>>n>>p;unsigned long long m=n,prod=1;while(m){prod*=(m%p+1);m/=p;}cout<<(n+1-prod)<<endl;}
