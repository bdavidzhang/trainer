#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int n=s.size(),b=0,p=0;
 for(int i=0;i<n;i++){b+=s[i]=='('?1:-1;if(b==0){p=i+1;break;}}
 string t=s.substr(p)+s.substr(0,p);
 if(t==s)puts("no");else puts(t.c_str());}
