#include <bits/stdc++.h>
using namespace std;
int main(){long long n;cin>>n;int L=to_string(n).size();long long tot=max(1,L-1);
for(int d=1;d<=9;d++){long long r=0;for(int i=0;i<L;i++)r=r*10+d;tot+=(r<=n)?L:L-1;}
cout<<tot<<endl;}
