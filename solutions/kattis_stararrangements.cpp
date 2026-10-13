#include <bits/stdc++.h>
using namespace std;
int main(){int s;scanf("%d",&s);printf("%d:\n",s);
for(int x=2;x<s;x++){int m=2*x-1;if(s%m==0||s%m==x)printf("%d,%d\n",x,x-1);if(s%x==0)printf("%d,%d\n",x,x);}}
