#include <bits/stdc++.h>
using namespace std;
int g;map<string,int> memo;
int go(string s){auto it=memo.find(s);if(it!=memo.end())return it->second;int b=0;
 for(int i=0;i+1<g;i++)if(s[i]!='R'&&s[i+1]!='L'){string t=s;t[i]='R';t[i+1]='L';b=max(b,1+go(t));}
 return memo[s]=b;}
int main(){int p;string s;cin>>g>>p>>s;puts(go(s)>=p?"1":"0");}
