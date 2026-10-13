#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;scanf("%d",&n);
    vector<double> x(n),y(n);
    for(int i=0;i<n;i++)scanf("%lf %lf",&x[i],&y[i]);
    double best=0;
    for(int i=1;i<n-1;i++){
        best=max(best,y[i]/(x[i]-x[0]));
        best=max(best,y[i]/(x[n-1]-x[i]));
    }
    printf("%.9f\n",atan(best)*180/M_PI);
}
