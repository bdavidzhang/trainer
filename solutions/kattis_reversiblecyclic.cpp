#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int n=s.size();if(n==1){puts("1");return 0;}
 string d=s+s;bool ok=true;
 for(int st=0;st<2;st++){string t=s.substr(st,n-1);reverse(t.begin(),t.end());if(d.find(t)==string::npos)ok=false;}
 puts(ok?"1":"0");}
