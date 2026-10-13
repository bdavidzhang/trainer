#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;unsigned long long r=0;for(int i=0;i<n;i++){string s;cin>>s;if(s[0]=='O')r|=1ULL<<(n-1-i);}cout<<r<<endl;}
