#include <bits/stdc++.h>
int main(){int g,r;scanf("%d %d",&g,&r);int p=std::min(g,r);g-=p;int a=p*10+(g/3)*10;g%=3;a+=g==2?3:g;printf("%d\n",a);}
