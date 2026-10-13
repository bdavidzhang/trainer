#include <bits/stdc++.h>
int main(){int n,x,m;scanf("%d %d %d",&n,&x,&m);int a=0,b=0;
for(int i=0;i<m;i++){int r;scanf("%d",&r);if(r<x)a++;else b++;}
printf("%d\n",a<b?a:b);}
