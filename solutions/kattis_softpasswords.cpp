#include <bits/stdc++.h>
using namespace std;
int main(){string s,p;cin>>s>>p;bool ok=s==p;
 if(s.size()==p.size()+1){ if(isdigit(s[0])&&s.substr(1)==p)ok=1; if(isdigit(s.back())&&s.substr(0,p.size())==p)ok=1;}
 string q=p;for(char&c:q){if(islower(c))c=toupper(c);else if(isupper(c))c=tolower(c);}
 if(q==s)ok=1;puts(ok?"Yes":"No");}
