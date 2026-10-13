#include <bits/stdc++.h>
using namespace std;
int main(){int k;string a,b;cin>>k>>a>>b;int n=a.size(),s=0;for(int i=0;i<n;i++)s+=a[i]==b[i];cout<<min(k,s)+min(n-k,n-s)<<endl;}
