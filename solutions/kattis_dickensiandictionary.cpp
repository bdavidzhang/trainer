#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;string L="qwertasdfgzxcvb";bool ok=true;
for(size_t i=1;i<s.size();i++){bool a=L.find(s[i-1])!=string::npos,b=L.find(s[i])!=string::npos;if(a==b)ok=false;}
puts(ok?"yes":"no");}
