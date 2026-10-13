#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;while(n--){string s;cin>>s;if(!s.empty()&&s.back()=='L')s.pop_back();
 string ip,fp;size_t d=s.find('.');if(d==string::npos)ip=s;else{ip=s.substr(0,d);fp=s.substr(d+1);}
 size_t k=0;while(k<ip.size()&&ip[k]=='0')k++;ip=ip.substr(k);if(ip.empty())ip="0";
 while(!fp.empty()&&fp.back()=='0')fp.pop_back();
 string r="v";for(char c:ip)r+=char('a'+(c-'0'));if(!fp.empty()){r+='p';for(char c:fp)r+=char('a'+(c-'0'));}
 cout<<r<<"\n";}}
