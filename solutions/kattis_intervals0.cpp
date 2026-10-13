#include <bits/stdc++.h>
using namespace std;
int main(){int n,k;scanf("%d %d",&n,&k);int c[25]={0};for(int i=0;i<n;i++){int a,b;scanf("%d %d",&a,&b);for(int h=a;h<b;h++)c[h]++;}int r=0;for(int h=0;h<24;h++)if(c[h]>=k)r++;printf("%d\n",r);}
