#include <bits/stdc++.h>
using namespace std;
int main(){int n,k;scanf("%d %d",&n,&k);int s=0;for(int i=0;i<k;i++){int r;scanf("%d",&r);s+=r;}
printf("%.9f %.9f\n",(s-3.0*(n-k))/n,(s+3.0*(n-k))/n);}
