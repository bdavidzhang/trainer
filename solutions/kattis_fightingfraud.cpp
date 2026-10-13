#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);unordered_map<string,int> st;bool ok=true;char a[32],b[32];
for(int i=0;i<n;i++){scanf("%s %s",a,b);int&s=st[b];if(a[0]=='p'){if(s!=0)ok=false;s=1;}else{if(s!=1)ok=false;s=2;}}
for(auto&p:st)if(p.second!=2)ok=false;puts(ok?"yes":"no");}
