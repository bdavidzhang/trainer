#include <bits/stdc++.h>
using namespace std;
int main(){
    double x,y; int n; scanf("%lf %lf %d",&x,&y,&n);
    double eff=y;
    for(int i=0;i<n;i++){ double l,u,f; scanf("%lf %lf %lf",&l,&u,&f); eff+=(u-l)*(f-1); }
    printf("%.10f\n",x/eff);
}
