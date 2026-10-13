#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;string t=s;for(char&c:t)c=tolower(c);cout<<t<<"\n";
for(size_t i=0;i+1<s.size();i++)if(s[i]=='S'&&s[i+1]=='S'){cout<<t.substr(0,i)<<"B"<<t.substr(i+2)<<"\n";}}
