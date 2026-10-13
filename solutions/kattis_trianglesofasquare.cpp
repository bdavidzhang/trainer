#include <bits/stdc++.h>
int main(){int x[2],y[2];scanf("%d %d %d %d",&x[0],&y[0],&x[1],&y[1]);int a=0;for(int i=0;i<2;i++){bool c=(x[i]==0||x[i]==2024)&&(y[i]==0||y[i]==2024);if(!c)a++;}printf("%d\n",a);}
