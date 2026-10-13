#include <bits/stdc++.h>
int main(){int n;scanf("%d",&n);long double s=0,t=1;for(int i=0;i<=n;i++){s+=t;t/=(i+1);if(t<1e-30L)break;}printf("%.15Lf\n",s);}
