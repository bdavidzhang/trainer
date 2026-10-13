#include <bits/stdc++.h>
using namespace std;
int main(){int n;string a,b;cin>>n>>a>>b;long long s=0;for(int i=0;i<n;i++){int d=abs(a[i]-b[i]);s+=min(d,26-d);}cout<<s<<"\n";}
