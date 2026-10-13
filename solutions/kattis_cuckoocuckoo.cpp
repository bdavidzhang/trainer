#include <bits/stdc++.h>
using namespace std;
int main(){int h,m,n;scanf("%d:%d",&h,&m);scanf("%d",&n);int c=0;
 while(true){ if(m==0)c+=h; else if(m%15==0)c+=1; if(c>=n)break; m++; if(m==60){m=0;h=h%12+1;} }
 printf("%02d:%02d\n",h,m);}
