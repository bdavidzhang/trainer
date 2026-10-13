#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int c[3]={0,0,0};int ans=0;
 for(char ch:s){c[ch-'A']++;ans=max(ans,max({c[0],c[1],c[2]})-min({c[0],c[1],c[2]}));}
 cout<<ans<<endl;}
