#include <bits/stdc++.h>
int main(){int a,b,k;scanf("%d %d %d",&a,&b,&k);int c=0;int d[32];
 for(int x=a;x<=b;x++){bool ok=true;for(int j=2;j<=k&&j<=x&&ok;j++){int m=0,y=x;while(y){d[m++]=y%j;y/=j;}for(int i=0;i<m-1-i;i++)if(d[i]!=d[m-1-i]){ok=false;break;}}c+=ok;}
 printf("%d\n",c);}
