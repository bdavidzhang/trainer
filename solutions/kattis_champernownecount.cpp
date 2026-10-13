#include <bits/stdc++.h>
using namespace std;
int main(){long long n,k;cin>>n>>k;long long cur=0,p=10;int cnt=0;
 for(long long i=1;i<=n;i++){if(i==p)p*=10;cur=(cur*(p%k)+i)%k;if(cur==0)cnt++;}
 cout<<cnt<<endl;}
