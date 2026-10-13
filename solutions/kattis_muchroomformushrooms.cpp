#include <bits/stdc++.h>
// No two adjacent columns can both hold stems; a stemless column gets at most 2 tiles (side caps of its two neighbours).
int main(){int r,c;scanf("%d %d",&r,&c);
if(c==1)puts("1");else if(r==1)printf("%d\n",(c+2)/3);else if(r==2)printf("%d\n",c/2+1);else puts("-1");}
