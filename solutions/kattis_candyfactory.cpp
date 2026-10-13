#include <bits/stdc++.h>
using namespace std;
int main(){long long n,k;cin>>n>>k;long long S=0,mx=0;for(int i=0;i<n;i++){long long x;cin>>x;S+=x;mx=max(mx,x);}
 long long P=max(mx,(S+k-1)/k);cout<<k*P-S<<endl;}
