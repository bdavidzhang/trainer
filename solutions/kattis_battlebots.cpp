#include <bits/stdc++.h>
using namespace std;
int main(){unsigned long long n;cin>>n;unsigned long long best=n;
for(int k=1;k<=62;k++){unsigned long long p=1ULL<<k;unsigned long long c=n/p+(n%p?1:0);best=min(best,k+c);}
cout<<best<<endl;}
