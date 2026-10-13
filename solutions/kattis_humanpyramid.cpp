#include <bits/stdc++.h>
using namespace std;
int main(){long long n;cin>>n;long long h=(long long)((sqrt(8.0L*n+1)-1)/2);
while(h*(h+1)/2>n)h--;while((h+1)*(h+2)/2<=n)h++;cout<<h<<"\n";}
