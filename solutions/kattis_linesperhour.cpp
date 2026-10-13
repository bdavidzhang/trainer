#include <bits/stdc++.h>
using namespace std;
int main(){int n,l;cin>>n>>l;vector<int>a(n);for(auto&x:a)cin>>x;sort(a.begin(),a.end());int s=0,c=0;for(int x:a){if(s+x<=5*l){s+=x;c++;}else break;}cout<<c<<"\n";}
