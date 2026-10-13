#include <bits/stdc++.h>
int main(){
    int n;scanf("%d",&n);
    double s=0;const double PI=acos(-1.0);
    while(n--){int a,d;scanf("%d %d",&a,&d);s+=d*sin(a*PI/180);}
    printf("%.2f\n",s);
}
