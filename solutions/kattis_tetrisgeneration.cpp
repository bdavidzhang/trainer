#include <bits/stdc++.h>
using namespace std;
int main(){int T;scanf("%d",&T);static char b[1005];while(T--){scanf("%s",b);int n=strlen(b);bool any=false;
 for(int off=0;off<7&&!any;off++){bool ok=true;int seen=0;for(int i=0;i<n&&ok;i++){if(i%7==off)seen=0;int bit=1<<(b[i]-'A');if(seen&bit)ok=false;seen|=bit;}if(ok)any=true;}
 puts(any?"1":"0");}}
