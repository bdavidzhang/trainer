#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;set<int>s;for(int i=0;i<n;i++){int x;cin>>x;s.insert(x);}
 int tot=1;for(int i=n;i<4;i++)tot*=6;int a=0;
 if((int)s.size()==n){a=1;for(int i=n;i<4;i++)a*=(6-i);}
 cout<<a<<" "<<tot-a<<endl;}
