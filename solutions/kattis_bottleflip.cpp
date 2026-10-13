#include <bits/stdc++.h>
using namespace std;
int main(){
    double h,r,da,dw;
    scanf("%lf %lf %lf %lf",&h,&r,&da,&dw);
    // optimum: centre of mass coincides with the water level x
    // (dw-da)/2 x^2 + da*h*x - da*h^2/2 = 0
    double x=h*(sqrt(da*dw)-da)/(dw-da);
    printf("%.10f\n",x);
}
