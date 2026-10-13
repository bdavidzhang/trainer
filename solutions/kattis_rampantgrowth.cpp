#include <bits/stdc++.h>
using namespace std;
int main(){long long r,c;cin>>r>>c;const long long M=998244353;long long a=r%M;for(int i=1;i<c;i++)a=a*(r-1)%M;cout<<a<<endl;}
