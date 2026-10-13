#include <bits/stdc++.h>
using namespace std;
const int MOD=9302023;
int main(){static char buf[1000005];scanf("%s",buf);string s(buf);int n=s.size();
 const char* w[10]={"zero","one","two","three","four","five","six","seven","eight","nine"};
 vector<int>d(n+1),c(n+1);d[0]=0;c[0]=1;
 for(int i=1;i<=n;i++){d[i]=d[i-1]+1;c[i]=c[i-1];
  for(int k=0;k<10;k++){int L=strlen(w[k]);if(i>=L&&s.compare(i-L,L,w[k])==0){int v=d[i-L]+1;
    if(v<d[i]){d[i]=v;c[i]=c[i-L];}else if(v==d[i]){c[i]=(c[i]+c[i-L])%MOD;}}}}
 printf("%d\n%d\n",d[n],c[n]);}
