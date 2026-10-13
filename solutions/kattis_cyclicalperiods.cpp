#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);int first[26],per[26];for(int i=0;i<26;i++)first[i]=per[i]=-1;
 // best: max period, then earliest discovery (position of 2nd occurrence == earliest first position), then order in string
 int bestP=-1,bestF=0;char best='?';
 for(int i=0;i<n;i++){int p;static char buf[64];scanf("%d %63s",&p,buf);
  for(char*q=buf;*q;q++){int c=*q-'a';if(first[c]<0)first[c]=p;else if(per[c]<0){per[c]=p-first[c];
    if(per[c]>bestP||(per[c]==bestP&&first[c]<bestF)){bestP=per[c];bestF=first[c];best=*q;}}}}
 printf("%c\n",best);}
