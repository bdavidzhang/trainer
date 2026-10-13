#include <bits/stdc++.h>
using namespace std;
string nxt(const string&s){int c[10]={0};for(char ch:s)c[ch-'0']++;string r;for(int d=0;d<10;d++)if(c[d])r+=to_string(c[d])+char('0'+d);return r;}
int main(){string n,m;cin>>n>>m;set<string> seen;string cur=n;
 for(int pos=1;pos<=100;pos++){
  if(cur==m){printf("%d\n",pos);return 0;}
  if(seen.count(cur)){puts("Does not appear");return 0;}
  seen.insert(cur);cur=nxt(cur);}
 if(seen.count(cur))puts("Does not appear");else puts("I'm bored");
}
