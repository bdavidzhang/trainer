#include <bits/stdc++.h>
using namespace std;
int main(){map<char,int>m;string s;int b=0;while(cin>>s)b=max(b,++m[s[0]]);cout<<b<<endl;}
