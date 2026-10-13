#include <bits/stdc++.h>
using namespace std;
static char buf[1000005];
int main(){int t;scanf("%d",&t);while(t--){scanf("%s",buf);int n=strlen(buf);set<int>ans;
 auto match=[&](int pos,int v)->int{ // returns length if buf at pos starts with v, else 0
   char tmp[8];int L=snprintf(tmp,8,"%d",v);if(pos+L>n)return 0;return memcmp(buf+pos,tmp,L)==0?L:0;};
 for(int L=1;L<=5&&L<=n;L++){ if(buf[0]=='0')break; int first=0;for(int i=0;i<L;i++)first=first*10+(buf[i]-'0');
   int cur=first,pos=L,skipped=-1;bool ok=true;
   while(pos<n){int m;
     if(cur+1<=99999&&(m=match(pos,cur+1))){cur++;pos+=m;}
     else if(skipped<0&&cur+2<=99999&&(m=match(pos,cur+2))){skipped=cur+1;cur+=2;pos+=m;}
     else{ok=false;break;}}
   if(!ok)continue;
   if(skipped>=0)ans.insert(skipped);
   else{if(first-1>=1)ans.insert(first-1);if(cur+1<=99999)ans.insert(cur+1);}}
 printf("%d\n",(int)ans.size());bool f=true;for(int x:ans){printf(f?"%d":" %d",x);f=false;}printf("\n");}}
